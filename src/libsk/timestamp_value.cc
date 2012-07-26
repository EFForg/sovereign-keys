// Copyright 2012 the SK authors. All rights reserved.

#include "timestamp_value.h"

#include <string>

#include "decimal_integer.h"
#include "slice.h"

namespace sk {

TimestampValue::TimestampValue() {
}

TimestampValue::TimestampValue(uint32_t timestamp)
  : timestamp_(timestamp) {
}

TimestampValue::~TimestampValue() {
}

void TimestampValue::AppendText(std::string* out) const {
  AppendDecimalInteger(static_cast<uint64_t>(timestamp_), out);
}

void TimestampValue::AppendBinary(std::string* out) const {
  out->append(1, timestamp_ & 0xff);
  out->append(1, (timestamp_ >> 8) & 0xff);
  out->append(1, (timestamp_ >> 16) & 0xff);
  out->append(1, (timestamp_ >> 24) & 0xff);
}

// static
TimestampValue* TimestampValue::ParseText(Slice in) {
  uint64_t value;
  if (!ReadDecimalInteger(in, &value))
    return NULL;
  if (value > 0xffffffff)
    // Out of range.
    return NULL;
  return new TimestampValue(static_cast<uint32_t>(value & 0xffffffff));
}

// static
TimestampValue* TimestampValue::ParseBinary(Slice* in) {
  if (in->length() < 4)
    // Need 4 bytes.
    return false;
  uint32_t value = (*in)[0] | ((*in)[1] << 8) | ((*in)[2] << 16) |
    ((*in)[3] << 24);
  in->Consume(4);
  return new TimestampValue(value);
}

}  // namespace sk
