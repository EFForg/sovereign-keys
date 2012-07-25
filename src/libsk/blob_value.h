// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_BLOB_VALUE_H_
#define LIBSK_BLOB_VALUE_H_

#include <string>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// BlobValue stores uninterpreted binary data.
class BlobValue : public Value {
 public:
  explicit BlobValue(std::string data);
  virtual ~BlobValue();

  const std::string& data() const { return data_; }
  void set_data(const std::string& str) { data_ = str; }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static BlobValue* ParseText(Slice in);
  static BlobValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(BlobValue);
  BlobValue();

  // The raw binary data in this blob.
  std::string data_;
};
}  // namespace sk

#endif  // LIBSK_BLOB_VALUE_H_
