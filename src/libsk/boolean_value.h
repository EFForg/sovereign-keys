// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_BOOLEAN_VALUE_H_
#define LIBSK_BOOLEAN_VALUE_H_

#include <string>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// BooleanValue stores true or false.
class BooleanValue : public Value {
 public:
  explicit BooleanValue(bool value);
  virtual ~BooleanValue();

  bool value() const { return value_; }
  void set_value(bool value) { value_ = value; }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static BooleanValue* ParseText(Slice in);
  static BooleanValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(BooleanValue);
  BooleanValue();

  // The boolean value.
  bool value_;
};
}  // namespace sk

#endif  // LIBSK_BOOLEAN_VALUE_H_
