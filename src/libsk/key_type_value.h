// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_KEY_TYPE_VALUE_H_
#define LIBSK_KEY_TYPE_VALUE_H_

#include <string>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// KeyTypeValue stores a key type enum.
class KeyTypeValue : public Value {
 public:
  enum KeyType {
    RSA = 0, ECC = 1
  };
  explicit KeyTypeValue(KeyType type);
  virtual ~KeyTypeValue();

  KeyType key_type() const { return type_; }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static KeyTypeValue* ParseText(Slice in);
  static KeyTypeValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(KeyTypeValue);
  KeyTypeValue();

  // The type of key.
  KeyType type_;
};
}  // namespace sk

#endif  // LIBSK_KEY_TYPE_VALUE_H_
