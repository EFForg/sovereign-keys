// Copyright 2012 the SK authors. All rights reserved.

#include "integer_value.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(IntegerValueTest, EncodeText) {
  string out;
  IntegerValue(0).AppendText(&out);
  EXPECT_EQ("0", out);
  out.clear();
  IntegerValue(18446744073709551615ULL).AppendText(&out);
  EXPECT_EQ("18446744073709551615", out);
}

TEST(IntegerValueTest, EncodeBinary) {
  string out;
  IntegerValue(0).AppendBinary(&out);
  EXPECT_EQ(1U, out.size());
  EXPECT_EQ(0, out[0]);
  out.clear();
  IntegerValue(18446744073709551615ULL).AppendBinary(&out);
  EXPECT_EQ(10U, out.size());
  EXPECT_EQ('\xFF', out[0]);
  EXPECT_EQ('\xFF', out[1]);
  EXPECT_EQ('\xFF', out[2]);
  EXPECT_EQ('\xFF', out[3]);
  EXPECT_EQ('\xFF', out[4]);
  EXPECT_EQ('\xFF', out[5]);
  EXPECT_EQ('\xFF', out[6]);
  EXPECT_EQ('\xFF', out[7]);
  EXPECT_EQ('\xFF', out[8]);
  EXPECT_EQ('\x01', out[9]);
}

TEST(IntegerValueTest, DecodeText) {
  unique_ptr<IntegerValue> value;
  value.reset(IntegerValue::ParseText("0"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(0U, value->value());
  value.reset(IntegerValue::ParseText("18446744073709551615"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(18446744073709551615ULL, value->value());
}

TEST(IntegerValueTest, DecodeBinary) {
  unique_ptr<IntegerValue> value;
  Slice in(string(1, 0));
  Slice orig_in = in;
  value.reset(IntegerValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(0U, value->value());
  EXPECT_EQ(1 + orig_in.data(), in.data());
  in = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x01";
  orig_in = in;
  value.reset(IntegerValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(18446744073709551615ULL, value->value());
}

TEST(IntegerValueTest, DecodeTextErrors) {
  // Invalid integer.
  unique_ptr<IntegerValue> value;
  value.reset(IntegerValue::ParseText(" 0"));
  EXPECT_TRUE(value.get() == NULL);
}

TEST(IntegerValueTest, DecodeBinaryErrors) {
  // Invalid varint.
  unique_ptr<IntegerValue> value;
  Slice in("\xFF");
  value.reset(IntegerValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
}

}  // namespace sk
