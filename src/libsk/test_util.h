// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_TEST_UTIL_H_
#define LIBSK_TEST_UTIL_H_

#include <string>

namespace sk {

class Descriptor;
class Slice;

namespace testing {

// Returns true iff fields in |desc| are well-formed.
bool CheckDescriptorFields(const Descriptor* desc);

// Includes the trailing nul on Slice |in| built from a string literal.
Slice WithNul(Slice in);

// Returns the binary contents of the ASCII hex string |in|.
std::string Unhex(Slice in);

// Returns the ASCII contents of the binary string |in|.
std::string Hex(Slice in);

}  // namespace testing
}  // namespace sk

#endif  // LIBSK_TEST_UTIL_H_
