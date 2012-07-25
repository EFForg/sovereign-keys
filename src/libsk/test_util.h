// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_TEST_UTIL_H_
#define LIBSK_TEST_UTIL_H_

namespace sk {

class Descriptor;
class Slice;

namespace testing {

// Returns true iff fields in |desc| are well-formed.
bool CheckDescriptorFields(const Descriptor* desc);

// Includes the trailing nul on Slice |in| built from a string literal.
Slice WithNul(Slice in);

}  // namespace testing
}  // namespace sk

#endif  // LIBSK_TEST_UTIL_H_
