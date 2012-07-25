// Copyright 2012 the SK authors. All rights reserved.

#include "bind_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(BindDescriptorTest, Sanity) {
  size_t prev_version_num_fields = 0;
  for (int version = 1; version < 255; version++) {
    if (BindDescriptor::IsVersionSupported(version)) {
      unique_ptr<BindDescriptor> desc(new BindDescriptor(version));
      ASSERT_TRUE(desc.get() != NULL);
      EXPECT_STREQ("Bind", desc->GetTypeName());
      EXPECT_EQ(0, desc->GetTypeId());
      EXPECT_LE(prev_version_num_fields, desc->GetNumFields());
      EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
      prev_version_num_fields = desc->GetNumFields();
    }
  }
}

TEST(BindDescriptorTest, V1FieldEnum) {
  ASSERT_TRUE(BindDescriptor::IsVersionSupported(1));
  unique_ptr<BindDescriptor> desc(new BindDescriptor(1));
  EXPECT_STREQ("CA-Cert-Chain",
      desc->GetField(BindDescriptor::kV1CACertChain).name);
  EXPECT_STREQ("Includes-Subdomains",
      desc->GetField(BindDescriptor::kV1IncludesSubdomains).name);
  EXPECT_STREQ("Key",
      desc->GetField(BindDescriptor::kV1Key).name);
  EXPECT_STREQ("Key-Type",
      desc->GetField(BindDescriptor::kV1KeyType).name);
  EXPECT_STREQ("Name",
      desc->GetField(BindDescriptor::kV1Name).name);
  EXPECT_STREQ("Rebinder-Names",
      desc->GetField(BindDescriptor::kV1RebinderNames).name);
  EXPECT_STREQ("SK-Signature",
      desc->GetField(BindDescriptor::kV1SKSignature).name);
  EXPECT_STREQ("SN",
      desc->GetField(BindDescriptor::kV1SN).name);
  EXPECT_STREQ("Services",
      desc->GetField(BindDescriptor::kV1Services).name);
  EXPECT_STREQ("Signature",
      desc->GetField(BindDescriptor::kV1Signature).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(BindDescriptor::kV1Timestamp).name);
}

}  // namespace sk
