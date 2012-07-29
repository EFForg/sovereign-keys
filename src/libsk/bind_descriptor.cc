// Copyright 2012 the SK authors. All rights reserved.

#include "bind_descriptor.h"

#include "descriptor.h"
#include "field.h"
#include "util.h"
#include "value.h"

namespace sk {

// static
const char* const BindDescriptor::kTypeName = "Bind";

// static
const int BindDescriptor::kTypeId = 1;

namespace {
const Field kBindFields[] = {
  // These must be sorted by field name.
  { "CA-Cert-Chain", Value::BLOB },
  { "Includes-Subdomains", Value::BOOLEAN },
  { "Key", Value::BLOB },
  { "Key-Type", Value::KEY_TYPE },
  { "Name", Value::STRING },
  { "Rebinder-Names", Value::REBINDER_NAMES },
  { "SK-Signature", Value::BLOB },
  { "SN", Value::INTEGER },
  { "Services", Value::SERVICES },
  { "Signature", Value::BLOB },
  { "TID", Value::INTEGER },
  { "Timestamp", Value::TIMESTAMP },
};
}  // namespace

BindDescriptor::BindDescriptor(int version)
  : Descriptor(version) {
}

BindDescriptor::~BindDescriptor() {
}

const char* BindDescriptor::GetTypeName() const {
  return kTypeName;
}

int BindDescriptor::GetTypeId() const {
  return kTypeId;
}

size_t BindDescriptor::GetNumFields() const {
  return arraysize(kBindFields);
}

const Field& BindDescriptor::GetField(size_t index) const {
  return kBindFields[index];
}
}  // namespace sk
