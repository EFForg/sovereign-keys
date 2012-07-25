// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_FIELD_H_
#define LIBSK_FIELD_H_

#include "value.h"

namespace sk {

// A single piece of data in a log entry.
struct Field {
  // The text that identifies this field in canonical form serialization.
  const char* const name;

  // The expected value type for this field.
  const Value::Type value_type;
};

}  // namespace sk

#endif  // LIBSK_LOG_ENTRY_FIELD_H_
