// Copyright 2012 the SK authors. All rights reserved.

#include "string_value.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "slice.h"
#include "test_util.h"

using sk::testing::WithNul;

using std::string;
using std::unique_ptr;

namespace sk {

TEST(StringValueTest, EncodeText) {
  string out;
  StringValue("test").AppendText(&out);
  EXPECT_EQ("test", out);
}

TEST(StringValueTest, EncodeBinary) {
  string out;
  StringValue("test").AppendBinary(&out);
  EXPECT_EQ(string("test") + string(1, 0), out);
}

TEST(StringValueTest, DecodeText) {
  unique_ptr<StringValue> str;
  str.reset(StringValue::ParseText("test"));
  ASSERT_TRUE(str.get() != NULL);
  EXPECT_EQ("test", str->text());
}

TEST(StringValueTest, DecodeBinary) {
  unique_ptr<StringValue> str;
  Slice in(WithNul("test"));
  Slice orig_in = in;
  str.reset(StringValue::ParseBinary(&in));
  ASSERT_TRUE(str.get() != NULL);
  EXPECT_EQ("test", str->text());
  EXPECT_EQ(orig_in.data() + 5, in.data());
}

TEST(StringValueTest, DecodeTextErrors) {
  unique_ptr<StringValue> str;
  // Empty strings are invalid.
  str.reset(StringValue::ParseText(""));
  EXPECT_TRUE(str.get() == NULL);
  // strings with non-printable characters are invalid.
  str.reset(StringValue::ParseText(std::string(1, 0)));
  EXPECT_TRUE(str.get() == NULL);
  str.reset(StringValue::ParseText(std::string(1, 7)));
  EXPECT_TRUE(str.get() == NULL);
}

TEST(StringValueTest, DecodeBinaryErrors) {
  unique_ptr<StringValue> str;
  // Empty strings are invalid.
  Slice in(string(1, 0));
  str.reset(StringValue::ParseBinary(&in));
  EXPECT_TRUE(str.get() == NULL);
  // Must be nul terminated.
  in = "no nul";
  str.reset(StringValue::ParseBinary(&in));
  EXPECT_TRUE(str.get() == NULL);
  // strings with non-printable characters are invalid.
  in = std::string(2, 0);
  str.reset(StringValue::ParseBinary(&in));
  EXPECT_TRUE(str.get() == NULL);
  in = std::string(1, 7) + std::string(1, 0);
  str.reset(StringValue::ParseBinary(&in));
  EXPECT_TRUE(str.get() == NULL);
}

}  // namespace sk
