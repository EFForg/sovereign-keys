// Copyright 2012 the SK authors. All rights reserved.

#include "remove_root_ca_descriptor.h"

#include "descriptor.h"
#include "field.h"
#include "util.h"
#include "value.h"

namespace sk {

// static
const char* const RemoveRootCADescriptor::kTypeName = "Remove-Root-CA";

// static
const int RemoveRootCADescriptor::kTypeId = 7;

namespace {
const Field kRemoveRootCAFields[] = {
  // These must be sorted by field name.
  { "CA-Cert-Hash", Value::BLOB },
  { "SN", Value::INTEGER },
  { "Signature", Value::BLOB },
  { "TID", Value::INTEGER },
  { "Timestamp", Value::TIMESTAMP },
};
}  // namespace

RemoveRootCADescriptor::RemoveRootCADescriptor(int version)
  : Descriptor(version) {
}

RemoveRootCADescriptor::~RemoveRootCADescriptor() {
}

const char* RemoveRootCADescriptor::GetTypeName() const {
  return kTypeName;
}

int RemoveRootCADescriptor::GetTypeId() const {
  return kTypeId;
}

size_t RemoveRootCADescriptor::GetNumFields() const {
  return arraysize(kRemoveRootCAFields);
}

const Field& RemoveRootCADescriptor::GetField(size_t index) const {
  return kRemoveRootCAFields[index];
}
}  // namespace sk
