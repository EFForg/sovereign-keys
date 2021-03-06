// Copyright 2012 the SK authors. All rights reserved.

#include "add_root_ca_descriptor.h"

#include "descriptor.h"
#include "field.h"
#include "util.h"
#include "value.h"

namespace sk {

// static
const char* const AddRootCADescriptor::kTypeName = "Add-Root-CA";

// static
const int AddRootCADescriptor::kTypeId = 6;

namespace {
const Field kAddRootCAFields[] = {
  // These must be sorted by field name.
  { "CA-Cert", Value::BLOB },
  { "SN", Value::INTEGER },
  { "Signature", Value::BLOB },
  { "TID", Value::INTEGER },
  { "Timestamp", Value::TIMESTAMP },
};
}  // namespace

AddRootCADescriptor::AddRootCADescriptor(int version)
  : Descriptor(version) {
}

AddRootCADescriptor::~AddRootCADescriptor() {
}

const char* AddRootCADescriptor::GetTypeName() const {
  return kTypeName;
}

int AddRootCADescriptor::GetTypeId() const {
  return kTypeId;
}

size_t AddRootCADescriptor::GetNumFields() const {
  return arraysize(kAddRootCAFields);
}

const Field& AddRootCADescriptor::GetField(size_t index) const {
  return kAddRootCAFields[index];
}
}  // namespace sk
