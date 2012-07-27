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

// Generates getter and setter methods for a value named |name| with native
// type |raw_type|.
#define PROPERTY(raw_type, name, value_prefix, index, getter) \
  raw_type name() { \
    return reinterpret_cast<value_prefix##Value*>(value(index))->getter(); \
  } \
  void set_##name(raw_type raw) { \
    set_value(index, new value_prefix##Value(raw)); \
  }

#endif  // VALUE_ACCESSORS_H_
