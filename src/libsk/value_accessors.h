// Copyright 2012 the SK authors. All rights reserved.

// This header should only be included from log entry subclasses to help
// generate code for getters and setters.

#ifndef VALUE_ACCESSORS_H_
#define VALUE_ACCESSORS_H_

#include "blob_value.h"
#include "boolean_value.h"
#include "integer_value.h"
#include "key_type_value.h"
#include "rebinder_names_value.h"
#include "services_value.h"
#include "string_value.h"
#include "timestamp_value.h"

// Generates code to retrieve a Value pointer of derived class |type| from 
// field number |index| in a log entry.
#define VALUE(type, index) \
  reinterpret_cast<type##Value*>(value(index))

// Generates getter and setter methods for a value named |name| with native
// type |raw_type|.
#define PROPERTY(raw_type, name, value, accessor) \
  raw_type name() { \
    return value->accessor(); \
  } \
  void set_##name(raw_type raw) { \
    value->set_##accessor(raw); \
  }

#endif  // VALUE_ACCESSORS_H_
