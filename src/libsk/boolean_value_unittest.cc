// Copyright 2012 the SK authors. All rights reserved.

#include "boolean_value.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(BooleanValueTest, EncodeText) {
  string out;
  BooleanValue(true).AppendText(&out);
  EXPECT_EQ("1", out);
  out.clear();
  BooleanValue(false).AppendText(&out);
  EXPECT_EQ("0", out);
}

TEST(BooleanValueTest, EncodeBinary) {
  string out;
  BooleanValue(true).AppendBinary(&out);
  EXPECT_EQ(1U, out.size());
  EXPECT_EQ(1, out[0]);
  out.clear();
  BooleanValue(false).AppendBinary(&out);
  EXPECT_EQ(1U, out.size());
  EXPECT_EQ(0, out[0]);
}

TEST(BooleanValueTest, DecodeText) {
  unique_ptr<BooleanValue> value;
  value.reset(BooleanValue::ParseText("0"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_FALSE(value->value());
  value.reset(BooleanValue::ParseText("1"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_TRUE(value->value());
}

TEST(BooleanValueTest, DecodeTextErrors) {
  unique_ptr<BooleanValue> value;
  value.reset(BooleanValue::ParseText(""));
  EXPECT_TRUE(value.get() == NULL);
  value.reset(BooleanValue::ParseText("11"));
  EXPECT_TRUE(value.get() == NULL);
  value.reset(BooleanValue::ParseText("2"));
  EXPECT_TRUE(value.get() == NULL);
  value.reset(BooleanValue::ParseText("true"));
  EXPECT_TRUE(value.get() == NULL);
  value.reset(BooleanValue::ParseText("false"));
  EXPECT_TRUE(value.get() == NULL);
}

TEST(BooleanValueTest, DecodeBinary) {
  unique_ptr<BooleanValue> value;
  Slice in(string(1, 0));
  Slice orig_in = in;
  value.reset(BooleanValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_FALSE(value->value());
  EXPECT_EQ(orig_in.data() + 1, in.data());
  in = Slice(string(1, 1));
  orig_in = in;
  value.reset(BooleanValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_TRUE(value->value());
  EXPECT_EQ(orig_in.data() + 1, in.data());
}

TEST(BooleanValueTest, DecodeBinaryErrors) {
  unique_ptr<BooleanValue> value;
  Slice in("");
  value.reset(BooleanValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
  in = "0";
  value.reset(BooleanValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
  in = "1";
  value.reset(BooleanValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
  in = string(1, 255);
  value.reset(BooleanValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
}

}  // namespace sk
