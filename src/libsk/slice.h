// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_SLICE_H_
#define LIBSK_SLICE_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>  // for memcmp
#include <string>

#include "util.h"

namespace sk {

// A Slice is a range of bytes in memory backed by a non-owned buffer.
// Users of this class must ensure the underlying buffer is valid.
// This is based on, but heavily pruned from Google's StringPiece as
// seen in e.g. RE2 and Chrome.
class Slice {
 public:
  typedef size_t size_type;
  typedef uint8_t value_type;
  typedef const value_type* pointer;
  typedef const value_type& reference;
  typedef const value_type& const_reference;
  typedef ptrdiff_t difference_type;
  typedef const value_type* const_iterator;

  static const size_type npos;

 public:
  Slice(const Slice& slice)
    : data_(slice.data()), length_(slice.length()) { }
  Slice(const std::string& str)
    : data_(reinterpret_cast<const uint8_t*>(str.data())),
      length_(str.size()) { }
  Slice(const char* data)
    : data_(reinterpret_cast<const uint8_t*>(data)),
      length_(strlen(data)) { }
  Slice(const uint8_t* data, size_t length)
    : data_(data), length_(length) { }

  const uint8_t *data() const { return data_; }
  size_t length() const { return length_; }
  uint8_t operator[](size_t i) const { return data_[i]; }

  // Consumes |num| bytes from the beginning of the slice.
  void Consume(size_t num) {
    data_ += num;
    length_ -= num;
  }

  // Consumes and returns the first byte of the slice.
  uint8_t ConsumeFirst() {
    const uint8_t value = data_[0];
    data_++;
    length_--;
    return value;
  }

  // Finds the first occurrence of |s| at or after |pos|.
  size_type Find(Slice s, size_type pos) const;

 private:
  Slice();

  const uint8_t* data_;
  size_t length_;
};

inline bool operator==(const Slice& x, const Slice& y) {
  return x.length() == y.length() &&
         memcmp(x.data(), y.data(), x.length()) == 0;
}

}  // namespace sk

#endif  // LIBSK_SLICE_H_
