// Copyright 2012 the SK authors. All rights reserved.

#include "key_type_value.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(KeyTypeValueTest, EncodeText) {
  string out;
  KeyTypeValue(KeyTypeValue::RSA).AppendText(&out);
  EXPECT_EQ("RSA", out);
  out.clear();
  KeyTypeValue(KeyTypeValue::ECC).AppendText(&out);
  EXPECT_EQ("ECC", out);
}

TEST(KeyTypeValueTest, EncodeBinary) {
  string out;
  KeyTypeValue(KeyTypeValue::RSA).AppendBinary(&out);
  EXPECT_EQ(1U, out.size());
  EXPECT_EQ(0, out[0]);
  out.clear();
  KeyTypeValue(KeyTypeValue::ECC).AppendBinary(&out);
  EXPECT_EQ(1U, out.size());
  EXPECT_EQ(1, out[0]);
}

TEST(KeyTypeValueTest, DecodeText) {
  unique_ptr<KeyTypeValue> key_type;
  key_type.reset(KeyTypeValue::ParseText("RSA"));
  ASSERT_TRUE(key_type.get() != NULL);
  EXPECT_EQ(KeyTypeValue::RSA, key_type->key_type());
  key_type.reset(KeyTypeValue::ParseText("ECC"));
  ASSERT_TRUE(key_type.get() != NULL);
  EXPECT_EQ(KeyTypeValue::ECC, key_type->key_type());
}

TEST(KeyTypeValueTest, DecodeBinary) {
  unique_ptr<KeyTypeValue> key_type;
  Slice in(string(1, 0));
  Slice orig_in = in;
  key_type.reset(KeyTypeValue::ParseBinary(&in));
  ASSERT_TRUE(key_type.get() != NULL);
  EXPECT_EQ(KeyTypeValue::RSA, key_type->key_type());
  EXPECT_EQ(1 + orig_in.data(), in.data());
  in = string(1, 1);
  orig_in = in;
  key_type.reset(KeyTypeValue::ParseBinary(&in));
  ASSERT_TRUE(key_type.get() != NULL);
  EXPECT_EQ(KeyTypeValue::ECC, key_type->key_type());
  EXPECT_EQ(1 + orig_in.data(), in.data());
}

TEST(KeyTypeValueTest, DecodeTextErrors) {
  unique_ptr<KeyTypeValue> key_type;
  key_type.reset(KeyTypeValue::ParseText(""));
  EXPECT_TRUE(key_type.get() == NULL);
  key_type.reset(KeyTypeValue::ParseText("RS"));
  EXPECT_TRUE(key_type.get() == NULL);
  key_type.reset(KeyTypeValue::ParseText("ECCC"));
  EXPECT_TRUE(key_type.get() == NULL);
}

TEST(KeyTypeValueTest, DecodeBinaryErrors) {
  unique_ptr<KeyTypeValue> key_type;
  Slice in("");
  key_type.reset(KeyTypeValue::ParseBinary(&in));
  EXPECT_TRUE(key_type.get() == NULL);
  in = "\x02";
  key_type.reset(KeyTypeValue::ParseBinary(&in));
  EXPECT_TRUE(key_type.get() == NULL);
}

}  // namespace sk
