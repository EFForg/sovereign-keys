// Copyright 2012 the SK authors. All rights reserved.

#include "blob_value.h"

#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {
namespace {
const char* const kLongBlob =
  "................................................................"
  "................................................................"
  "................................................................"
  "...............................................................";
const char* const kLongBlobBase64 =
  "Li4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4u"
  "Li4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4u"
  "Li4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4u"
  "Li4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4u"
  "Li4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4uLi4u"
  "Li4uLi4uLi4uLi4uLi4u";
const int kLongBlobLength = 255;
}

TEST(BlobValueTest, EncodeText) {
  string out;
  BlobValue("blobby test").AppendText(&out);
  EXPECT_EQ("YmxvYmJ5IHRlc3Q=", out);
  out.clear();
  BlobValue("").AppendText(&out);
  EXPECT_TRUE(out.empty());
  out.clear();
  BlobValue(kLongBlob).AppendText(&out);
  EXPECT_EQ(kLongBlobBase64, out);
}

TEST(BlobValueTest, EncodeBinary) {
  string out;
  BlobValue("blobby test").AppendBinary(&out);
  EXPECT_EQ(12U, out.size());
  EXPECT_EQ(11, out[0]);
  EXPECT_EQ("blobby test", out.substr(1));
  out.clear();
  BlobValue("").AppendBinary(&out);
  EXPECT_EQ(1U, out.size());
  EXPECT_EQ(0, out[0]);
  out.clear();
  BlobValue(kLongBlob).AppendBinary(&out);
  EXPECT_EQ(257U, out.size());
  EXPECT_EQ('\xFF', out[0]);
  EXPECT_EQ(1, out[1]);
  EXPECT_EQ(kLongBlob, out.substr(2));
}

TEST(BlobValueTest, DecodeText) {
  unique_ptr<BlobValue> value;
  value.reset(BlobValue::ParseText("YmxvYmJ5IHRlc3Q="));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ("blobby test", value->data());
  value.reset(BlobValue::ParseText(""));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_TRUE(value->data().empty());
  value.reset(BlobValue::ParseText(kLongBlobBase64));
  EXPECT_EQ(kLongBlob, value->data());
}

TEST(BlobValueTest, DecodeTextErrors) {
  unique_ptr<BlobValue> value(BlobValue::ParseText("not base64"));
  EXPECT_TRUE(value.get() == NULL);
}

TEST(BlobValueTest, DecodeBinary) {
  unique_ptr<BlobValue> value;
  Slice in("\013blobby test");
  Slice orig_in = in;
  value.reset(BlobValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ("blobby test", value->data());
  EXPECT_EQ(orig_in.data() + 12, in.data());
  in = string(1, 0);
  orig_in = in;
  value.reset(BlobValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_TRUE(value->data().empty());
  EXPECT_EQ(orig_in.data() + 1, in.data());
  in = string("\xFF\x01") + string(kLongBlob);
  orig_in = in;
  value.reset(BlobValue::ParseBinary(&in));
  ASSERT_TRUE(value.get() != NULL);
  EXPECT_EQ(kLongBlob, value->data());
  EXPECT_EQ(orig_in.data() + 257, in.data());
}

TEST(BlobValueTest, DecodeBinaryErrors) {
  unique_ptr<BlobValue> value;

  // Invalid varint (empty).
  Slice in("");
  value.reset(BlobValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);

  // Truncated value.
  in = "\013blobby tes";
  value.reset(BlobValue::ParseBinary(&in));
  EXPECT_TRUE(value.get() == NULL);
}

}  // namespace sk
