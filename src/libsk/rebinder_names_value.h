// Copyright 2012 the SK authors. All rights reserved.

#ifndef LIBSK_REBINDER_NAMES_VALUE_H_
#define LIBSK_REBINDER_NAMES_VALUE_H_

#include <string>
#include <vector>

#include "value.h"
#include "util.h"

namespace sk {

class Slice;

// RebinderNamesValue stores a list of authorized rebinder names in a
// Bind entry.
class RebinderNamesValue : public Value {
 public:
  explicit RebinderNamesValue(const std::vector<std::string>& names);
  virtual ~RebinderNamesValue();

  const std::vector<std::string>& rebinder_names() const { return names_; }
  void set_rebinder_names(const std::vector<std::string>& names) {
    names_ = names;
  }

  // Value interface:
  virtual void AppendText(std::string* out) const OVERRIDE;
  virtual void AppendBinary(std::string* out) const OVERRIDE;
  static RebinderNamesValue* ParseText(Slice in);
  static RebinderNamesValue* ParseBinary(Slice* in);

 private:
  DISALLOW_EVIL_CONSTRUCTORS(RebinderNamesValue);
  RebinderNamesValue();

  // A list of rebinder names.
  std::vector<std::string> names_;
};
}  // namespace sk

#endif  // LIBSK_REBINDER_NAMES_VALUE_H_
