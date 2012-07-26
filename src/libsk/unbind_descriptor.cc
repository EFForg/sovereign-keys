// Copyright 2012 the SK authors. All rights reserved.

#include "unbind_descriptor.h"

#include "descriptor.h"
#include "field.h"
#include "util.h"
#include "value.h"

namespace sk {

// static
const char* const UnbindDescriptor::kTypeName = "Unbind";

// static
const int UnbindDescriptor::kTypeId = 2;

namespace {
const Field kUnbindFields[] = {
  // These must be sorted by field name.
  { "Last-Secure-Timestamp", Value::INTEGER },
  { "Name", Value::STRING },
  { "SK-Signature", Value::BLOB },
  { "SN", Value::INTEGER },
  { "Signature", Value::BLOB },
  { "TID", Value::INTEGER },
  { "Timestamp", Value::TIMESTAMP },
};
}  // namespace

UnbindDescriptor::UnbindDescriptor(int version)
  : Descriptor(version) {
}

UnbindDescriptor::~UnbindDescriptor() {
}

const char* UnbindDescriptor::GetTypeName() const {
  return kTypeName;
}

int UnbindDescriptor::GetTypeId() const {
  return kTypeId;
}

size_t UnbindDescriptor::GetNumFields() const {
  return arraysize(kUnbindFields);
}

const Field& UnbindDescriptor::GetField(size_t index) const {
  return kUnbindFields[index];
}

// static
bool UnbindDescriptor::IsVersionSupported(int version) {
  return version == 1;
}

}  // namespace sk
