// Copyright 2012 the SK authors. All rights reserved.

#include "slice.h"

#include <algorithm>

namespace sk {

Slice::Slice()
  : data_(NULL), length_(0) {
}

Slice::size_type Slice::Find(Slice s, size_type pos) const {
  if (pos > static_cast<size_type>(length_))
    return npos;

  const value_type* result = std::search(data_ + pos, data_ + length_,
                                         s.data_, s.data_ + s.length_);
  const size_type match_pos = result - data_;
  return match_pos + s.length_ <= length_ ? match_pos : npos;
}

// static
const Slice::size_type Slice::npos = size_type(-1);

}  // namespace sk
