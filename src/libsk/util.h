// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_UTIL_H_
#define LIBSK_UTIL_H_

#include <algorithm>
#include <stddef.h>

namespace sk {

// Returns the size of its argument array.
template<class Type, ptrdiff_t n>
ptrdiff_t arraysize(Type (&)[n]) {
  return n;
}

}  // namespace sk

// Annotate a virtual method indicating it must be overriding a virtual
// method in the parent class.
// Use like:
//   virtual void foo() OVERRIDE;
#if defined(COMPILER_MSVC)
#define OVERRIDE override
#elif defined(__clang__)
#define OVERRIDE override
#else
#define OVERRIDE
#endif

// Annotate a function indicating the caller must examine the return value.
// Use like:
//   int foo() WARN_UNUSED_RESULT;
// To explicitly ignore a result, see |ignore_result()| in <base/basictypes.h>.
#if defined(COMPILER_GCC)
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define WARN_UNUSED_RESULT
#endif

// DISALLOW_EVIL_CONSTRUCTORS disallows the copy and operator= functions.
// It goes in the private: declarations in a class.
#define DISALLOW_EVIL_CONSTRUCTORS(TypeName) \
  TypeName(const TypeName&);                 \
  void operator=(const TypeName&)

#endif  // LIBSK_UTIL_H_
