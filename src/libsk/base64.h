// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_BASE64_H_
#define LIBSK_BASE64_H_

#include <string>

#include "util.h"

namespace sk {

class Slice;

// Encodes |in| using URL-safe base64 and appends the result to |out|.
void AppendBase64(Slice in, std::string* out);

// Decodes URL-safe base64 from |in| and appends the result to |out|.
// Returns true iff the entire input was decoded successfully.
bool ReadBase64(Slice in, std::string* out) WARN_UNUSED_RESULT;

}  // namespace sk

#endif  // LIBSK_BASE64_H_
