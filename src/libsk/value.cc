// Copyright 2012 the SK authors. All rights reserved.

#include "value.h"

#include "blob_value.h"
#include "boolean_value.h"
#include "integer_value.h"
#include "key_type_value.h"
#include "rebinder_names_value.h"
#include "string_value.h"
#include "services_value.h"
#include "timestamp_value.h"
#include "slice.h"

namespace sk {

Value::~Value() {
}

// static
Value* Value::ParseText(Type type, Slice in) {
  switch (type) {
  case BLOB: return BlobValue::ParseText(in);
  case STRING: return StringValue::ParseText(in);
  case TIMESTAMP: return TimestampValue::ParseText(in);
  case INTEGER: return IntegerValue::ParseText(in);
  case BOOLEAN: return BooleanValue::ParseText(in);
  case KEY_TYPE: return KeyTypeValue::ParseText(in);
  case SERVICES: return ServicesValue::ParseText(in);
  case REBINDER_NAMES: return RebinderNamesValue::ParseText(in);
  default: break;
  }
  return NULL;
}

// static
Value* Value::ParseBinary(Type type, Slice* in) {
  switch (type) {
  case BLOB: return BlobValue::ParseBinary(in);
  case STRING: return StringValue::ParseBinary(in);
  case TIMESTAMP: return TimestampValue::ParseBinary(in);
  case INTEGER: return IntegerValue::ParseBinary(in);
  case BOOLEAN: return BooleanValue::ParseBinary(in);
  case KEY_TYPE: return KeyTypeValue::ParseBinary(in);
  case SERVICES: return ServicesValue::ParseBinary(in);
  case REBINDER_NAMES: return RebinderNamesValue::ParseBinary(in);
  default: break;
  }
  return NULL;
}

}  // namespace sk
