// Copyright 2012 the SK authors. All rights reserved.

#include "tfm_descriptor.h"

#include "descriptor.h"
#include "field.h"
#include "util.h"
#include "value.h"

namespace sk {

// static
const char* const TFMDescriptor::kTypeName = "TFM";

// static
const int TFMDescriptor::kTypeId = 0;

namespace {
const Field kTFMFields[] = {
  // These must be sorted by field name.
  { "Max-Published-SN", Value::INTEGER },
  { "Max-Published-Timestamp", Value::INTEGER },
  { "Max-SN", Value::INTEGER },
  { "Max-Timestamp", Value::INTEGER },
  { "Signature", Value::BLOB },
  { "TID", Value::INTEGER },
  { "Timestamp", Value::TIMESTAMP },
};
}  // namespace

TFMDescriptor::TFMDescriptor(int version)
  : Descriptor(version) {
}

TFMDescriptor::~TFMDescriptor() {
}

const char* TFMDescriptor::GetTypeName() const {
  return kTypeName;
}

int TFMDescriptor::GetTypeId() const {
  return kTypeId;
}

size_t TFMDescriptor::GetNumFields() const {
  return arraysize(kTFMFields);
}

const Field& TFMDescriptor::GetField(size_t index) const {
  return kTFMFields[index];
}

// static
bool TFMDescriptor::IsVersionSupported(int version) {
  return version == 1;
}

}  // namespace sk
