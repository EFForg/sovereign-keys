// Copyright 2012 the SK authors. All rights reserved.

#include "change_services_descriptor.h"

#include "descriptor.h"
#include "field.h"
#include "util.h"
#include "value.h"

namespace sk {

// static
const char* const ChangeServicesDescriptor::kTypeName = "Change-Services";

// static
const int ChangeServicesDescriptor::kTypeId = 4;

namespace {
const Field kChangeServicesFields[] = {
  // These must be sorted by field name.
  { "Name", Value::STRING },
  { "SK-Signature", Value::BLOB },
  { "SN", Value::INTEGER },
  { "Services", Value::SERVICES },
  { "Signature", Value::BLOB },
  { "TID", Value::INTEGER },
  { "Timestamp", Value::TIMESTAMP },
};
}  // namespace

ChangeServicesDescriptor::ChangeServicesDescriptor(int version)
  : Descriptor(version) {
}

ChangeServicesDescriptor::~ChangeServicesDescriptor() {
}

const char* ChangeServicesDescriptor::GetTypeName() const {
  return kTypeName;
}

int ChangeServicesDescriptor::GetTypeId() const {
  return kTypeId;
}

size_t ChangeServicesDescriptor::GetNumFields() const {
  return arraysize(kChangeServicesFields);
}

const Field& ChangeServicesDescriptor::GetField(size_t index) const {
  return kChangeServicesFields[index];
}
}  // namespace sk
