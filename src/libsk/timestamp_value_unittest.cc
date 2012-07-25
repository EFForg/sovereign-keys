// Copyright 2012 the SK authors. All rights reserved.

#include "timestamp_value.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(TimestampValueTest, EncodeText) {
  string out;
  TimestampValue(1342883754).AppendText(&out);
  EXPECT_EQ("1342883754", out);
  out.clear();
  TimestampValue(4294967295).AppendText(&out);
  EXPECT_EQ("4294967295", out);
}

TEST(TimestampValueTest, EncodeBinary) {
  string out;
  TimestampValue(1342883754).AppendBinary(&out);
  EXPECT_EQ("\xAA\xC7\x0A\x50", out);
  out.clear();
  TimestampValue(4294967295).AppendBinary(&out);
  EXPECT_EQ("\xFF\xFF\xFF\xFF", out);
}

TEST(TimestampValueTest, DecodeText) {
  unique_ptr<TimestampValue> timestamp;
  timestamp.reset(TimestampValue::ParseText("1342883754"));
  ASSERT_TRUE(timestamp.get() != NULL);
  EXPECT_EQ(1342883754U, timestamp->timestamp());
  timestamp.reset(TimestampValue::ParseText("4294967295"));
  ASSERT_TRUE(timestamp.get() != NULL);
  EXPECT_EQ(4294967295U, timestamp->timestamp());
}

TEST(TimestampValueTest, DecodeBinary) {
  unique_ptr<TimestampValue> timestamp;
  Slice in("\xAA\xC7\x0A\x50");
  Slice orig_in = in;
  timestamp.reset(TimestampValue::ParseBinary(&in));
  ASSERT_TRUE(timestamp.get() != NULL);
  EXPECT_EQ(1342883754U, timestamp->timestamp());
  EXPECT_EQ(orig_in.data() + 4, in.data());
  in = "\xFF\xFF\xFF\xFF";
  orig_in = in;
  timestamp.reset(TimestampValue::ParseBinary(&in));
  ASSERT_TRUE(timestamp.get() != NULL);
  EXPECT_EQ(4294967295U, timestamp->timestamp());
  EXPECT_EQ(orig_in.data() + 4, in.data());
}

TEST(TimestampValueTest, DecodeTextErrors) {
  unique_ptr<TimestampValue> timestamp;
  // Invalid decimal integers.
  timestamp.reset(TimestampValue::ParseText(""));
  EXPECT_TRUE(timestamp.get() == NULL);
  timestamp.reset(TimestampValue::ParseText("01"));
  EXPECT_TRUE(timestamp.get() == NULL);
  // Out of range.
  timestamp.reset(TimestampValue::ParseText("4294967296"));
  EXPECT_TRUE(timestamp.get() == NULL);
}

TEST(TimestampValueTest, DecodeBinaryErrors) {
  unique_ptr<TimestampValue> timestamp;
  // Not enough bytes.
  Slice in("");
  timestamp.reset(TimestampValue::ParseBinary(&in));
  EXPECT_TRUE(timestamp.get() == NULL);
  in = "\xFF\xFF\x01";
  timestamp.reset(TimestampValue::ParseBinary(&in));
  EXPECT_TRUE(timestamp.get() == NULL);
}

}  // namespace sk
