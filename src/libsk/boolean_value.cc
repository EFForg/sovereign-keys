#include "boolean_value.h"

#include <string>

#include "slice.h"

namespace sk {

BooleanValue::BooleanValue() {
}

BooleanValue::BooleanValue(bool value)
  : value_(value) {
}

BooleanValue::~BooleanValue() {
}

void BooleanValue::AppendText(std::string* out) const {
  out->append(1, value_ ? '1' : '0');
}

void BooleanValue::AppendBinary(std::string* out) const {
  out->append(1, static_cast<char>(value_));
}

// static
BooleanValue* BooleanValue::ParseText(Slice in) {
  if (in.length() != 1 || (in[0] != '0' && in[0] != '1'))
    // Must be 0 or 1.
    return NULL;
  return new BooleanValue(in[0] == '1');
}

// static
BooleanValue* BooleanValue::ParseBinary(Slice* in) {
  if (in->length() == 0)
    return NULL;
  uint8_t value = in->ConsumeFirst();
  if (value != 0 && value != 1)
    // Must be 0 or 1.
    return NULL;
  return new BooleanValue(value);
}

}  // namespace sk
