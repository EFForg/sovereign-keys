// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_VARINT_H_
#define LIBSK_VARINT_H_

#include <stdint.h>
#include <string>

#include "util.h"

namespace sk {

class Slice;

// Decodes a varint of up to 64 bits from |in| and stores it to |out|.
// Returns true iff a valid varint was found.
bool ReadVarint(Slice *in, uint64_t* out) WARN_UNUSED_RESULT;

// Encodes |in| as a varint and stores it to |out|.
void AppendVarint(uint64_t in, std::string* out);

}  // namespace sk

#endif  // LIBSK_VARINT_H_
