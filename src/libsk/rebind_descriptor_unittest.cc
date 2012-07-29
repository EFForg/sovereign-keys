// Copyright 2012 the SK authors. All rights reserved.

#include "rebind_descriptor.h"

#include <memory>
#include <stddef.h>

#include "field.h"
#include "gtest/gtest.h"
#include "test_util.h"

using std::unique_ptr;

namespace sk {

TEST(RebindDescriptorTest, Sanity) {
  unique_ptr<RebindDescriptor> desc(new RebindDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("Rebind", desc->GetTypeName());
  EXPECT_EQ(3, desc->GetTypeId());
  EXPECT_TRUE(testing::CheckDescriptorFields(desc.get()));
}

TEST(RebindDescriptorTest, Fields) {
  unique_ptr<RebindDescriptor> desc(new RebindDescriptor(1));
  ASSERT_TRUE(desc.get() != NULL);
  EXPECT_STREQ("CA-Cert-Chain",
      desc->GetField(RebindDescriptor::kCACertChain).name);
  EXPECT_STREQ("Includes-Subdomains",
      desc->GetField(RebindDescriptor::kIncludesSubdomains).name);
  EXPECT_STREQ("Key",
      desc->GetField(RebindDescriptor::kKey).name);
  EXPECT_STREQ("Key-Type",
      desc->GetField(RebindDescriptor::kKeyType).name);
  EXPECT_STREQ("Name",
      desc->GetField(RebindDescriptor::kName).name);
  EXPECT_STREQ("Rebinder-Name",
      desc->GetField(RebindDescriptor::kRebinderName).name);
  EXPECT_STREQ("Rebinder-Names",
      desc->GetField(RebindDescriptor::kRebinderNames).name);
  EXPECT_STREQ("Rebinder-Signature",
      desc->GetField(RebindDescriptor::kRebinderSignature).name);
  EXPECT_STREQ("SK-Signature",
      desc->GetField(RebindDescriptor::kSKSignature).name);
  EXPECT_STREQ("SN",
      desc->GetField(RebindDescriptor::kSN).name);
  EXPECT_STREQ("Services",
      desc->GetField(RebindDescriptor::kServices).name);
  EXPECT_STREQ("Signature",
      desc->GetField(RebindDescriptor::kSignature).name);
  EXPECT_STREQ("TID",
      desc->GetField(RebindDescriptor::kTID).name);
  EXPECT_STREQ("Timestamp",
      desc->GetField(RebindDescriptor::kTimestamp).name);
}

}  // namespace sk
