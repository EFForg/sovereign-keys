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
  unique_ptr<TFMDescriptor> desc(new TFMDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("TFM", desc->GetTypeName());
  EXPECT_EQ(0, desc->GetTypeId());
  EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
}

TEST(TFMDescriptorTest, Fields) {
  unique_ptr<TFMDescriptor> desc(new TFMDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
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
