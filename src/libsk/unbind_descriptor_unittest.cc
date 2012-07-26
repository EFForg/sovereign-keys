// Copyright 2012 the SK authors. All rights reserved.

#include "unbind_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(UnbindDescriptorTest, Sanity) {
  size_t prev_version_num_fields = 0;
  for (int version = 1; version < 255; version++) {
    if (UnbindDescriptor::IsVersionSupported(version)) {
      unique_ptr<UnbindDescriptor> desc(new UnbindDescriptor(version));
      ASSERT_TRUE(desc.get() != NULL);
      EXPECT_STREQ("Unbind", desc->GetTypeName());
      EXPECT_EQ(2, desc->GetTypeId());
      EXPECT_LE(prev_version_num_fields, desc->GetNumFields());
      EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
      prev_version_num_fields = desc->GetNumFields();
    }
  }
}

TEST(UnbindDescriptorTest, Fields) {
  ASSERT_TRUE(UnbindDescriptor::IsVersionSupported(1));
  unique_ptr<UnbindDescriptor> desc(new UnbindDescriptor(1));
  EXPECT_STREQ("Last-Secure-Timestamp",
      desc->GetField(UnbindDescriptor::kLastSecureTimestamp).name);
  EXPECT_STREQ("Name",
      desc->GetField(UnbindDescriptor::kName).name);
  EXPECT_STREQ("SK-Signature",
      desc->GetField(UnbindDescriptor::kSKSignature).name);
  EXPECT_STREQ("SN",
      desc->GetField(UnbindDescriptor::kSN).name);
  EXPECT_STREQ("Signature",
      desc->GetField(UnbindDescriptor::kSignature).name);
  EXPECT_STREQ("TID",
      desc->GetField(UnbindDescriptor::kTID).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(UnbindDescriptor::kTimestamp).name);
}

}  // namespace sk
