// Copyright 2012 the SK authors. All rights reserved.

#include "remove_root_ca_entry.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "descriptor.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(RemoveRootCAEntryTest, Accessors) {
  unique_ptr<RemoveRootCAEntry> entry(RemoveRootCAEntry::ParseText(
    "Remove-Root-CA: 1\n"
    "CA-Cert-Hash: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(entry.get() != NULL);
  ASSERT_TRUE(entry->descriptor() != NULL);
  EXPECT_STREQ("Remove-Root-CA", entry->descriptor()->GetTypeName());
  EXPECT_EQ(1, entry->descriptor()->GetVersion());
  EXPECT_EQ("...", entry->ca_cert_hash());
  EXPECT_EQ(42U, entry->sn());
  EXPECT_EQ("...", entry->signature());
  EXPECT_EQ(0U, entry->tid());
  EXPECT_EQ(1342885825U, entry->timestamp());
}

TEST(RemoveRootCAEntryTest, Setters) {
  unique_ptr<RemoveRootCAEntry> entry(new RemoveRootCAEntry(1));
  entry->set_ca_cert_hash("...");
  entry->set_sn(42);
  entry->set_signature("...");
  entry->set_tid(0);
  entry->set_timestamp(1342885825);
  string out;
  entry->AppendText(&out);
  EXPECT_EQ(
    "Remove-Root-CA: 1\n"
    "CA-Cert-Hash: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n",
    out);
}

}  // namespace sk
