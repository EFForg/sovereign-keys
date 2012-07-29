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
  unique_ptr<UnbindDescriptor> desc(new UnbindDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("Unbind", desc->GetTypeName());
  EXPECT_EQ(2, desc->GetTypeId());
  EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
}

TEST(UnbindDescriptorTest, Fields) {
  unique_ptr<UnbindDescriptor> desc(new UnbindDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
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
