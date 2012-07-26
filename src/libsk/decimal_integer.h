// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_DECIMAL_INTEGER_H_
#define LIBSK_DECIMAL_INTEGER_H_

#include <stdint.h>
#include <string>

#include "util.h"

namespace sk {

class Slice;

// Reads a decimal integer from |in| and saves its value to |value|.
// Returns true iff |in| parses correctly.
bool ReadDecimalInteger(Slice in, uint64_t* value) WARN_UNUSED_RESULT;

// Appends decimal encoding of |value| to |out|.
void AppendDecimalInteger(uint64_t value, std::string* out);

}  // namespace sk

#endif  // LIBSK_DECIMAL_INTEGER_H_
