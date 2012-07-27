// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_TIMESTAMP_VALUE_H_
#define LIBSK_TIMESTAMP_VALUE_H_

#include <stdint.h>
#include <string>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// A |TimestampValue| stores a POSIX timestamp with 32 bits of resolution.
class TimestampValue : public Value {
 public:
  explicit TimestampValue(uint32_t timestamp);
  virtual ~TimestampValue();

  uint32_t timestamp() const { return timestamp_; }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static TimestampValue* ParseText(Slice in);
  static TimestampValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(TimestampValue);
  TimestampValue();

  // The raw POSIX timestamp.
  uint32_t timestamp_;
};
}  // namespace sk

#endif  // LIBSK_TIMESTAMP_VALUE_H_
