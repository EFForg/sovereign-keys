// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_STRING_VALUE_H_
#define LIBSK_STRING_VALUE_H_

#include <string>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// A |StringValue| stores a printable ASCII character string.
class StringValue : public Value {
 public:
  explicit StringValue(std::string text);
  virtual ~StringValue();

  const std::string& text() const { return text_; }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static StringValue* ParseText(Slice in);
  static StringValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(StringValue);
  StringValue();

  // The text of the string.
  std::string text_;
};
}  // namespace sk

#endif  // LIBSK_STRING_VALUE_H_
