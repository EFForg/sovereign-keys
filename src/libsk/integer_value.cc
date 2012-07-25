// Copyright 2012 the SK authors. All rights reserved.

#include "integer_value.h"

#include <stddef.h>

#include "decimal_integer.h"
#include "slice.h"
#include "varint.h"

namespace sk {

IntegerValue::IntegerValue() {
}

IntegerValue::IntegerValue(uint64_t value)
  : value_(value) {
}

IntegerValue::~IntegerValue() {
}

void IntegerValue::AppendText(std::string* out) const {
  AppendDecimalInteger(value_, out);
}

void IntegerValue::AppendBinary(std::string* out) const {
  AppendVarint(value_, out);
}

// static
IntegerValue* IntegerValue::ParseText(Slice in) {
  uint64_t value;
  if (!ReadDecimalInteger(in, &value))
    return NULL;
  return new IntegerValue(value);
}

// static
IntegerValue* IntegerValue::ParseBinary(Slice* in) {
  uint64_t value;
  if (!ReadVarint(in, &value))
    return NULL;
  return new IntegerValue(value);
}

}  // namespace sk
