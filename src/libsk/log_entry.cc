#include "log_entry.h"

#include <algorithm>
#include <stddef.h>
#include <memory>
#include <vector>

#include "bind_descriptor.h"
#include "descriptor.h"
#include "decimal_integer.h"
#include "field.h"
#include "slice.h"
#include "value.h"

namespace sk {
namespace {
// The maximum version number for a log entry.
// This is constrained by the binary encoding which uses one unsigned byte
// to encode a version number.
const unsigned int kMaxVersion = 255;

// Splits |in| into a series of key-value pairs. Keys and values are
// delimited by ": " and pairs by "\n". Appends key and value Slices to
// |pairs|. Returns true iff the pairs parse correctly.
bool SplitFields(Slice in, std::vector<LogEntry::KeyValuePair>* pairs) {
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
    pairs->push_back(LogEntry::KeyValuePair(
          Slice(in.data(), end_key),
          Slice(in.data() + end_key + 2, end_pair - (end_key + 2))));
    in.Consume(end_pair + 1);
  }
  // Truncated.
  return false;
}
}  // namespace

LogEntry::LogEntry(const Descriptor* descriptor)
  : descriptor_(descriptor) {
}

LogEntry::~LogEntry() {
  delete descriptor_;
  for (size_t i = 0; i < values_.size(); i++)
    delete values_[i];
}

void LogEntry::AppendText(std::string* out) const {
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

void LogEntry::AppendBinary(std::string* out) const {
  out->append(1, descriptor_->GetTypeId());
  out->append(1, descriptor_->GetVersion());
  const size_t num_values = values_.size();
  for (size_t i = 0; i < num_values; i++)
    values_[i]->AppendBinary(out);
}

// static
LogEntry* LogEntry::ParseText(Slice in) {
  std::vector<KeyValuePair> pairs;
  if (!SplitFields(in, &pairs) || pairs.empty())
    return NULL;
  uint64_t version = 0;
  if (!ReadDecimalInteger(pairs[0].second, &version) ||
      version > kMaxVersion)
    return NULL;
  if (pairs[0].first == BindDescriptor::kTypeName &&
      BindDescriptor::IsVersionSupported(version))
    return ParseTextFields(new BindDescriptor(version), pairs);
  return NULL;
}

// static
LogEntry* LogEntry::ParseBinary(Slice* in) {
  if (in->length() < 2)
    return NULL;
  const uint8_t entry_type = in->ConsumeFirst();
  const uint8_t version = in->ConsumeFirst();
  if (entry_type == BindDescriptor::kTypeId &&
      BindDescriptor::IsVersionSupported(version))
    return ParseBinaryFields(new BindDescriptor(version), in);
  return NULL;
}

LogEntry* LogEntry::ParseTextFields(
    const Descriptor* descriptor,
    const std::vector<KeyValuePair>& pairs) {
  std::unique_ptr<const Descriptor> descriptor_deleter(descriptor);
  const size_t num_fields = descriptor->GetNumFields();
  if (num_fields != pairs.size() - 1)
    return NULL;
  std::unique_ptr<LogEntry> entry(
      new LogEntry(descriptor_deleter.release()));
  entry->values_.resize(num_fields, NULL);
  for (size_t i = 0; i < num_fields; i++) {
    const Field& spec = descriptor->GetField(i);
    if (!(pairs[i + 1].first == spec.name))
      return NULL;
    entry->values_[i] = Value::ParseText(spec.value_type,
        pairs[i + 1].second);
    if (entry->values_[i] == NULL)
      return NULL;
  }
  return entry.release();
}

LogEntry* LogEntry::ParseBinaryFields(
    const Descriptor* descriptor,
    Slice* in) {
  std::unique_ptr<LogEntry> entry(new LogEntry(descriptor));
  const size_t num_fields = descriptor->GetNumFields();
  entry->values_.resize(num_fields, NULL);
  for (size_t i = 0; i < num_fields; i++) {
    if (in->length() == 0)
      // Truncated.
      return NULL;
    const Field& spec = descriptor->GetField(i);
    entry->values_[i] = Value::ParseBinary(spec.value_type, in);
  }
  return entry.release();
}

}  // namespace sk
