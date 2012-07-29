// Copyright 2012 the SK authors. All rights reserved.

#include "rebind_descriptor.h"

#include "descriptor.h"
#include "field.h"
#include "util.h"
#include "value.h"

namespace sk {

// static
const char* const RebindDescriptor::kTypeName = "Rebind";

// static
const int RebindDescriptor::kTypeId = 3;

namespace {
const Field kRebindFields[] = {
  // These must be sorted by field name.
  { "CA-Cert-Chain", Value::BLOB },
  { "Includes-Subdomains", Value::BOOLEAN },
  { "Key", Value::BLOB },
  { "Key-Type", Value::KEY_TYPE },
  { "Name", Value::STRING },
  { "Rebinder-Name", Value::STRING },
  { "Rebinder-Names", Value::REBINDER_NAMES },
  { "Rebinder-Signature", Value::BLOB },
  { "SK-Signature", Value::BLOB },
  { "SN", Value::INTEGER },
  { "Services", Value::SERVICES },
  { "Signature", Value::BLOB },
  { "TID", Value::INTEGER },
  { "Timestamp", Value::TIMESTAMP },
};
}  // namespace

RebindDescriptor::RebindDescriptor(int version)
  : Descriptor(version) {
}

RebindDescriptor::~RebindDescriptor() {
}

const char* RebindDescriptor::GetTypeName() const {
  return kTypeName;
}

int RebindDescriptor::GetTypeId() const {
  return kTypeId;
}

size_t RebindDescriptor::GetNumFields() const {
  return arraysize(kRebindFields);
}

const Field& RebindDescriptor::GetField(size_t index) const {
  return kRebindFields[index];
}
}  // namespace sk
