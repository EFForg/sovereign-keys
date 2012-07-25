// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_INTEGER_VALUE_H_
#define LIBSK_INTEGER_VALUE_H_

#include <stdint.h>
#include <string>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// IntegerValue stores a non-negative integer.
class IntegerValue : public Value {
 public:
  explicit IntegerValue(uint64_t value);
  virtual ~IntegerValue();

  uint64_t value() const { return value_; }
  void set_value(uint64_t value) { value_ = value; }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static IntegerValue* ParseText(Slice in);
  static IntegerValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(IntegerValue);
  IntegerValue();

  // The integer.
  uint64_t value_;
};

}  // namespace sk

#endif  // LIBSK_INTEGER_VALUE_H_
