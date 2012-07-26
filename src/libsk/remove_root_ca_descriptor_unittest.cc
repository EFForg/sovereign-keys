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
  size_t prev_version_num_fields = 0;
  for (int version = 1; version < 255; version++) {
    if (RemoveRootCADescriptor::IsVersionSupported(version)) {
      unique_ptr<RemoveRootCADescriptor> desc(new RemoveRootCADescriptor(version));
      ASSERT_TRUE(desc.get() != NULL);
      EXPECT_STREQ("Remove-Root-CA", desc->GetTypeName());
      EXPECT_EQ(-1, desc->GetTypeId());
      EXPECT_LE(prev_version_num_fields, desc->GetNumFields());
      EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
      prev_version_num_fields = desc->GetNumFields();
    }
  }
}

TEST(RemoveRootCADescriptorTest, Fields) {
  ASSERT_TRUE(RemoveRootCADescriptor::IsVersionSupported(1));
  unique_ptr<RemoveRootCADescriptor> desc(new RemoveRootCADescriptor(1));
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
