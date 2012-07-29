// Copyright 2012 the SK authors. All rights reserved.

#include "message.h"

#include <algorithm>
#include <stddef.h>
#include <memory>
#include <vector>

#include "add_root_ca_entry.h"
#include "bind_entry.h"
#include "change_services_entry.h"
#include "decimal_integer.h"
#include "descriptor.h"
#include "field.h"
#include "rebind_entry.h"
#include "remove_root_ca_entry.h"
#include "slice.h"
#include "tfm.h"
#include "unbind_entry.h"
#include "value.h"

// This list is used to generate factories to instantiate message instances
// by type names encoded in ASCII or binary. It should be sorted by expected
// popularity of a message type.
#define MESSAGE_TYPES(op) \
  op(BindEntry); \
  op(TFM); \
  op(ChangeServicesEntry); \
  op(UnbindEntry); \
  op(RebindEntry); \
  op(AddRootCAEntry); \
  op(RemoveRootCAEntry); \

namespace sk {
namespace {
// A key and an associated value.
typedef std::pair<Slice, Slice> KeyValuePair;

// The maximum version number for a message type.
// This is constrained by the binary encoding which uses one unsigned byte
// to encode a version number.
const unsigned int kMaxVersion = 255;

// Splits |in| into a series of key-value pairs. Keys and values are
// delimited by ": " and pairs by "\n". Appends key and value Slices to
// |pairs|. Returns true iff the pairs parse correctly.
bool SplitFields(Slice in, std::vector<KeyValuePair>* pairs) {
  while (in.length() > 0) {
    if (in[0] == '\n') {
      // A trailing newline ends the list of pairs.
      in.ConsumeFirst();
      return true;
    }
    size_t end_key = in.Find(": ", 0);
    size_t end_pair = in.Find("\n", 0);
    if (end_key == Slice::npos || end_pair == Slice::npos) {
      // Unterminated key or pair.
      return false;
    }
    if (end_key > end_pair) {
      // There is no value for this key.
      return false;
    }
    // Do not include newline in the value.
    pairs->push_back(KeyValuePair(
          Slice(in.data(), end_key),
          Slice(in.data() + end_key + 2, end_pair - (end_key + 2))));
    in.Consume(end_pair + 1);
  }
  // Truncated.
  return false;
}

// Returns a new message of the type identified by |name| and |version|,
// or NULL if there is no such message type.
Message* NewMessageByName(Slice name, int version) {
#define BUILD(type) \
  if (type::GetDescriptor(version) != NULL && \
      name == type::GetDescriptor(version)->GetTypeName()) \
    return new type(version);
  MESSAGE_TYPES(BUILD);
  return NULL;
#undef BUILD
}

// Returns a new message of the type identified by |message_type| and |version|,
// or NULL if there is no such message type.
Message* NewMessageByType(int message_type, int version) {
#define BUILD(type) \
  if (type::GetDescriptor(version) != NULL && \
      message_type == type::GetDescriptor(version)->GetTypeId()) \
    return new type(version);
  MESSAGE_TYPES(BUILD);
  return NULL;
#undef BUILD
}
}  // namespace

Message::Message(const Descriptor* descriptor)
  : descriptor_(descriptor),
    values_(descriptor_ ? descriptor->GetNumFields() : 0, NULL) {
}

Message::~Message() {
  for (size_t i = 0; i < values_.size(); i++)
    delete values_[i];
}

void Message::AppendText(std::string* out) const {
  const size_t num_values = values_.size();
  out->append(descriptor_->GetTypeName());
  out->append(": ");
  AppendDecimalInteger(descriptor_->GetVersion(), out);
  out->append("\n");
  for (size_t i = 0; i < num_values; i++) {
    out->append(descriptor_->GetField(i).name);
    out->append(": ");
    values_[i]->AppendText(out);
    out->append("\n");
  }
  out->append("\n");
}

void Message::AppendBinary(std::string* out) const {
  out->append(1, descriptor_->GetTypeId());
  out->append(1, descriptor_->GetVersion());
  const size_t num_values = values_.size();
  for (size_t i = 0; i < num_values; i++)
    values_[i]->AppendBinary(out);
}

// static
Message* Message::ParseText(Slice in) {
  std::vector<KeyValuePair> pairs;
  if (!SplitFields(in, &pairs) || pairs.empty())
    return NULL;
  uint64_t version = 0;
  if (!ReadDecimalInteger(pairs[0].second, &version) ||
      version > kMaxVersion)
    return NULL;
  std::unique_ptr<Message> message(NewMessageByName(pairs[0].first, version));
  if (message == NULL)
    return NULL;
  const Descriptor* descriptor = message->descriptor();
  if (descriptor == NULL)
    return NULL;
  const size_t num_fields = descriptor->GetNumFields();
  if (num_fields != pairs.size() - 1)
    return NULL;
  for (size_t i = 0; i < num_fields; i++) {
    const Field& spec = descriptor->GetField(i);
    if (!(pairs[i + 1].first == spec.name))
      return NULL;
    message->set_value(i, Value::ParseText(spec.value_type,
        pairs[i + 1].second));
    if (message->value(i) == NULL)
      return NULL;
  }
  return message.release();
}

// static
Message* Message::ParseBinary(Slice* in) {
  if (in->length() < 2)
    return NULL;
  const uint8_t message_type = in->ConsumeFirst();
  const uint8_t version = in->ConsumeFirst();
  std::unique_ptr<Message> message(NewMessageByType(message_type, version));
  if (message == NULL)
    return NULL;
  const Descriptor* descriptor = message->descriptor();
  if (descriptor == NULL)
    return NULL;
  const size_t num_fields = descriptor->GetNumFields();
  for (size_t i = 0; i < num_fields; i++) {
    if (in->length() == 0)
      // Truncated.
      return NULL;
    const Field& spec = descriptor->GetField(i);
    message->set_value(i, Value::ParseBinary(spec.value_type, in));
    if (message->value(i) == NULL)
      return NULL;
  }
  return message.release();
}

}  // namespace sk
