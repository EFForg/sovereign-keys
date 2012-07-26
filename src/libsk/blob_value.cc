// Copyright 2012 the SK authors. All rights reserved.

#include "blob_value.h"

#include "base64.h"
#include "slice.h"
#include "varint.h"

namespace sk {

BlobValue::BlobValue() {
}

BlobValue::BlobValue(std::string data)
  : data_(data) {
}

BlobValue::~BlobValue() {
}

void BlobValue::AppendText(std::string* out) const {
  AppendBase64(data_, out);
}

void BlobValue::AppendBinary(std::string* out) const {
  AppendVarint(data_.size(), out);
  out->append(data_);
}

// static
BlobValue* BlobValue::ParseText(Slice in) {
  std::string data;
  if (!ReadBase64(in, &data))
    return NULL;
  return new BlobValue(data);
}

// static
BlobValue* BlobValue::ParseBinary(Slice* in) {
  uint64_t length;
  if (!ReadVarint(in, &length))
    return NULL;
  if (in->length() < length)
    return NULL;
  const char* data = reinterpret_cast<const char*>(in->data());
  in->Consume(length);
  return new BlobValue(std::string(data, length));
}

}  // namespace sk
