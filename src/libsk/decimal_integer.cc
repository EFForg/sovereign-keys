#include "decimal_integer.h"

#include "slice.h"

namespace sk {

bool ReadDecimalInteger(Slice in, uint64_t* value) {
  if (in.length() == 0)
    return false;
  *value = 0;
  while (in.length() > 0) {
    const uint8_t digit = in.ConsumeFirst();
    if (in.length() != 0 && (*value) == 0 && digit == '0')
      // Leading zeros are illegal so that encodings are distinct.
      return false;
    if (digit < '0' || digit > '9')
      // Not a digit.
      return false;
    uint64_t next_value = 10 * (*value) + (digit - '0');
    if (next_value < (*value))
      // value doesn't fit in 64 bits.
      return false;
    *value = next_value;
  }
  return true;
}

void AppendDecimalInteger(uint64_t value, std::string* out) {
  char buf[32];
  int i;
  for (i = sizeof(buf) - 1; ; i--) {
    buf[i] = '0' + (value % 10);
    value /= 10;
    if (value == 0)
      break;
  }
  out->append(buf + i, sizeof(buf) - i);
}

}
