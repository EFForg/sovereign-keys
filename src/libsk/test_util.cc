// Copyright 2012 the SK authors. All rights reserved.

#include "test_util.h"

#include <algorithm>
#include <vector>
#include <string>

#include "descriptor.h"
#include "field.h"
#include "slice.h"
#include "value.h"

using std::sort;
using std::string;
using std::vector;

namespace sk {
namespace testing {
namespace {
vector<string> Sort(const vector<string>& vec) {
  vector<string> sorted(vec.begin(), vec.end());
  sort(sorted.begin(), sorted.end());
  return sorted;
}

char HexDigit(int value) {
  return "0123456789abcdef"[value];
}

int HexDigitValue(char c) {
  if (c >= '0' && c <= '9')
    return c - '0';
  if (c >= 'a' && c <= 'f')
    return 10 + c - 'a';
  if (c >= 'A' && c <= 'F')
    return 10 + c - 'A';
  return 0;
}
}  // namespace

bool CheckDescriptorFields(const Descriptor* desc) {
  // There must be fields present.
  if (desc->GetNumFields() == 0)
    return false;

  // Each field should have a valid value type.
  for (size_t i = 0; i < desc->GetNumFields(); i++)
    if (desc->GetField(i).value_type < 0 ||
        desc->GetField(i).value_type >= Value::NUM_VALUE_TYPES)
      return false;

  // Field names must be sorted.
  vector<string> field_names;
  for (size_t i = 0; i < desc->GetNumFields(); i++)
    field_names.push_back(desc->GetField(i).name);
  vector<string> sorted_field_names(Sort(field_names));
  if (field_names != sorted_field_names)
    return false;

  // There should be no duplicate field names.
  for (size_t i = 1; i < sorted_field_names.size(); i++)
    if (sorted_field_names[i] == sorted_field_names[i - 1])
      return false;

  return true;
}

Slice WithNul(Slice in) {
  return Slice(in.data(), in.length() + 1);
}

string Unhex(Slice in) {
  string out;
  for (size_t i = 0; i < in.length(); i += 2)
    out.append(1, 16 * HexDigitValue(in[i]) + HexDigitValue(in[i + 1]));
  return out;
}

string Hex(Slice in) {
  string out;
  for (size_t i = 0; i < in.length(); i++) {
    out.append(1, HexDigit((in[i] >> 4) & 15));
    out.append(1, HexDigit(in[i] & 15));
  }
  return out;
}
}  // namespace testing
}  // namespace sk
