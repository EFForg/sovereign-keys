// Copyright 2012 the SK authors. All rights reserved.

#include "add_root_ca_entry.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "descriptor.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(AddRootCAEntryTest, Getters) {
  unique_ptr<AddRootCAEntry> entry(AddRootCAEntry::ParseText(
    "Add-Root-CA: 1\n"
    "CA-Cert: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(entry.get() != NULL);
  EXPECT_EQ("...", entry->ca_cert());
  EXPECT_EQ(42U, entry->sn());
  EXPECT_EQ("...", entry->signature());
  EXPECT_EQ(0U, entry->tid());
  EXPECT_EQ(1342885825U, entry->timestamp());
}

TEST(AddRootCAEntryTest, Setters) {
  unique_ptr<AddRootCAEntry> entry(new AddRootCAEntry(1));
  entry->set_ca_cert("...");
  entry->set_sn(42);
  entry->set_signature("...");
  entry->set_tid(0);
  entry->set_timestamp(1342885825);
  string out;
  entry->AppendText(&out);
  EXPECT_EQ(
    "Add-Root-CA: 1\n"
    "CA-Cert: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n",
    out);
}

}  // namespace sk
