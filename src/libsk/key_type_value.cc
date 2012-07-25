#include "key_type_value.h"

#include <ctype.h>
#include <string>

#include "slice.h"

namespace sk {
namespace {
const char* const kRSAType = "RSA";
const char* const kECCType = "ECC";
}

KeyTypeValue::KeyTypeValue() {
}

KeyTypeValue::KeyTypeValue(KeyType type)
  : type_(type) {
}

KeyTypeValue::~KeyTypeValue() {
}

void KeyTypeValue::AppendText(std::string* out) const {
  out->append(type_ == RSA ? kRSAType : kECCType);
}

void KeyTypeValue::AppendBinary(std::string* out) const {
  out->append(1, type_ == RSA ? 0 : 1);
}

// static
KeyTypeValue* KeyTypeValue::ParseText(Slice in) {
  if (in.length() != 3)
    // Must be 3 characters long.
    return NULL;
  if (!(in == kRSAType || in == kECCType))
    // Must be either RSA or ECC.
    return NULL;
  return new KeyTypeValue(in == kRSAType ? RSA : ECC);
}

// static
KeyTypeValue* KeyTypeValue::ParseBinary(Slice* in) {
  if (in->length() == 0)
    // Cannot be empty.
    return NULL;
  uint8_t value = in->ConsumeFirst();
  if (!(value == 0 || value == 1))
    // Must be either 0 or 1.
    return NULL;
  return new KeyTypeValue(value == 0 ? RSA : ECC);
}

}  // namespace sk
