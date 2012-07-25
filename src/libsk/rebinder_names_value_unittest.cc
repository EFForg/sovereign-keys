// Copyright 2012 the SK authors. All rights reserved.

#include "rebinder_names_value.h"

#include <string>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "slice.h"
#include "test_util.h"
#include "util.h"

using sk::testing::WithNul;

using std::string;
using std::unique_ptr;
using std::vector;

namespace sk {

TEST(RebinderNamesValueTest, EncodeText) {
  string out;
  RebinderNamesValue(vector<string>()).AppendText(&out);
  EXPECT_EQ("none", out);
  out.clear();
  RebinderNamesValue(vector<string>({"foo"})).AppendText(&out);
  EXPECT_EQ("foo", out);
  out.clear();
  RebinderNamesValue(vector<string>({"foo","bar"})).AppendText(&out);
  EXPECT_EQ("foo,bar", out);
  out.clear();
  RebinderNamesValue(vector<string>({"foo","bar","baz","quux"}))
    .AppendText(&out);
  EXPECT_EQ("foo,bar,baz,quux", out);
}

TEST(RebinderNamesValueTest, EncodeBinary) {
  string out;
  RebinderNamesValue(vector<string>()).AppendBinary(&out);
  EXPECT_EQ(string("none") + string(1, 0), out);
  out.clear();
  RebinderNamesValue(vector<string>({"foo"})).AppendBinary(&out);
  EXPECT_EQ(string("foo") + string(1, 0), out);
  out.clear();
  RebinderNamesValue(vector<string>({"foo","bar"})).AppendBinary(&out);
  EXPECT_EQ(string("foo,bar") + string(1, 0), out);
  out.clear();
  RebinderNamesValue(vector<string>({"foo","bar","baz","quux"}))
    .AppendBinary(&out);
  EXPECT_EQ(string("foo,bar,baz,quux") + string(1, 0), out);
}

TEST(RebinderNamesValueTest, DecodeText) {
  unique_ptr<RebinderNamesValue> value;
  value.reset(RebinderNamesValue::ParseText("none"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(0U, value->rebinder_names().size());
  value.reset(RebinderNamesValue::ParseText("foo"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(1U, value->rebinder_names().size());
  EXPECT_EQ("foo", value->rebinder_names()[0]);
  value.reset(RebinderNamesValue::ParseText("foo,bar"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(2U, value->rebinder_names().size());
  EXPECT_EQ("foo", value->rebinder_names()[0]);
  EXPECT_EQ("bar", value->rebinder_names()[1]);
  value.reset(RebinderNamesValue::ParseText("foo,bar,baz,quux"));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(4U, value->rebinder_names().size());
  EXPECT_EQ("foo", value->rebinder_names()[0]);
  EXPECT_EQ("bar", value->rebinder_names()[1]);
  EXPECT_EQ("baz", value->rebinder_names()[2]);
  EXPECT_EQ("quux", value->rebinder_names()[3]);
}

TEST(RebinderNamesValueTest, DecodeBinary) {
  unique_ptr<RebinderNamesValue> value;
  Slice in(WithNul("none"));
  Slice orig_in = in;
  value.reset(RebinderNamesValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(0U, value->rebinder_names().size());
  EXPECT_EQ(orig_in.data() + 5, in.data());
  in = WithNul("foo");
  orig_in = in;
  value.reset(RebinderNamesValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(1U, value->rebinder_names().size());
  EXPECT_EQ("foo", value->rebinder_names()[0]);
  EXPECT_EQ(orig_in.data() + 4, in.data());
  in = WithNul("foo,bar");
  orig_in = in;
  value.reset(RebinderNamesValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(2U, value->rebinder_names().size());
  EXPECT_EQ("foo", value->rebinder_names()[0]);
  EXPECT_EQ("bar", value->rebinder_names()[1]);
  EXPECT_EQ(orig_in.data() + 8, in.data());
  in = WithNul("foo,bar,baz,quux");
  orig_in = in;
  value.reset(RebinderNamesValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(4U, value->rebinder_names().size());
  EXPECT_EQ("foo", value->rebinder_names()[0]);
  EXPECT_EQ("bar", value->rebinder_names()[1]);
  EXPECT_EQ("baz", value->rebinder_names()[2]);
  EXPECT_EQ("quux", value->rebinder_names()[3]);
  EXPECT_EQ(orig_in.data() + 17, in.data());
}

TEST(RebinderNamesValueTest, DecodeTextErrors) {
  unique_ptr<RebinderNamesValue> value;
  value.reset(RebinderNamesValue::ParseText(""));
  EXPECT_TRUE(value.get() == NULL);
  value.reset(RebinderNamesValue::ParseText(","));
  EXPECT_TRUE(value.get() == NULL);
  value.reset(RebinderNamesValue::ParseText("a,"));
  EXPECT_TRUE(value.get() == NULL);
  value.reset(RebinderNamesValue::ParseText("a,,"));
  EXPECT_TRUE(value.get() == NULL);
}

TEST(RebinderNamesValueTest, DecodeBinaryErrors) {
  unique_ptr<RebinderNamesValue> value;
  Slice in(string(1, 0));
  value.reset(RebinderNamesValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
  in = WithNul(",");
  value.reset(RebinderNamesValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
  in = WithNul("a,");
  value.reset(RebinderNamesValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
  in = WithNul("a,,");
  value.reset(RebinderNamesValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
}

}  // namespace sk
