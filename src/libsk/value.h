// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_VALUE_H_
#define LIBSK_VALUE_H_

#include <string>

namespace sk {

class Slice;

// Interface for accessing field data. Value type instances are immutable.
class Value {
 public:
  // Possible types of values. Used in log entry descriptors to specify the
  // type of each field. Each of these corresponds to a subclass of Value.
  enum Type {
    // Raw binary data. Used for storing signatures and DERs.
    BLOB = 0,
 
    // ACSII string with unspecified contents. Used for domain names.
    STRING = 1,
 
    // POSIX timestamp.
    TIMESTAMP = 2,
 
    // An unsigned integer of at most 64 bits.
    INTEGER = 3,
 
    // True or false.
    BOOLEAN = 4,
 
    // A string that names a public key type (e.g. RSA or ECC).
    KEY_TYPE = 5,
 
    // A string that lists routes for services on a host.
    SERVICES = 6,
 
    // A string that lists other domains which can rebind a key for a name
    // after revokation.
    REBINDER_NAMES = 7,

    // The number of types in this enum.
    NUM_VALUE_TYPES
  };

  virtual ~Value();

  // Appends the value to a string in canonical text format.
  virtual void AppendText(std::string* out) const = 0;

  // Appends the value to a string in binary wire protocol format.
  virtual void AppendBinary(std::string* out) const = 0;

  // Each value type should implement the following static factory methods.

  // Parses a value of type |type| from |in| and returns a derived instance.
  static Value* ParseText(Type type, Slice in);

  // Parses a value of type |type| from |in| and returns a derived instance.
  // Advances |in| to the next byte past the value.
  static Value* ParseBinary(Type type, Slice* in);
};

}  // namespace sk

#endif  // LIBSK_VALUE_H_
