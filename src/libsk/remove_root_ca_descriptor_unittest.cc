// Copyright 2012 the SK authors. All rights reserved.

#include "remove_root_ca_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(RemoveRootCADescriptorTest, Sanity) {
  unique_ptr<RemoveRootCADescriptor> desc(new RemoveRootCADescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("Remove-Root-CA", desc->GetTypeName());
  EXPECT_EQ(7, desc->GetTypeId());
  EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
}

TEST(RemoveRootCADescriptorTest, Fields) {
  unique_ptr<RemoveRootCADescriptor> desc(new RemoveRootCADescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("CA-Cert-Hash",
      desc->GetField(RemoveRootCADescriptor::kCACertHash).name);
  EXPECT_STREQ("SN",
      desc->GetField(RemoveRootCADescriptor::kSN).name);
  EXPECT_STREQ("Signature",
      desc->GetField(RemoveRootCADescriptor::kSignature).name);
  EXPECT_STREQ("TID",
      desc->GetField(RemoveRootCADescriptor::kTID).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(RemoveRootCADescriptor::kTimestamp).name);
}

}  // namespace sk
