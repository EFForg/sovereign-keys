// Copyright 2012 the SK authors. All rights reserved.

#include "tfm_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(TFMDescriptorTest, Sanity) {
  size_t prev_version_num_fields = 0;
  for (int version = 1; version < 255; version++) {
    if (TFMDescriptor::IsVersionSupported(version)) {
      unique_ptr<TFMDescriptor> desc(new TFMDescriptor(version));
      ASSERT_TRUE(desc.get() != NULL);
      EXPECT_STREQ("TFM", desc->GetTypeName());
      EXPECT_EQ(0, desc->GetTypeId());
      EXPECT_LE(prev_version_num_fields, desc->GetNumFields());
      EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
      prev_version_num_fields = desc->GetNumFields();
    }
  }
}

TEST(TFMDescriptorTest, Fields) {
  ASSERT_TRUE(TFMDescriptor::IsVersionSupported(1));
  unique_ptr<TFMDescriptor> desc(new TFMDescriptor(1));
  EXPECT_STREQ("Max-Published-SN",
      desc->GetField(TFMDescriptor::kMaxPublishedSN).name);
  EXPECT_STREQ("Max-Published-Timestamp",
      desc->GetField(TFMDescriptor::kMaxPublishedTimestamp).name);
  EXPECT_STREQ("Max-SN",
      desc->GetField(TFMDescriptor::kMaxSN).name);
  EXPECT_STREQ("Max-Timestamp",
      desc->GetField(TFMDescriptor::kMaxTimestamp).name);
  EXPECT_STREQ("Signature",
      desc->GetField(TFMDescriptor::kSignature).name);
  EXPECT_STREQ("TID",
      desc->GetField(TFMDescriptor::kTID).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(TFMDescriptor::kTimestamp).name);
}

}  // namespace sk
