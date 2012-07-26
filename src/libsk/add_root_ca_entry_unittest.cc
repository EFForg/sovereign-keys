#include "add_root_ca_entry.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "descriptor.h"
#include "log_entry.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(AddRootCAEntryTest, Accessors) {
  unique_ptr<AddRootCAEntry> entry(AddRootCAEntry::ParseText(
    "Add-Root-CA: 1\n"
    "CA-Cert: Li4u\n"
    "SN: 42\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(entry.get() != NULL);
  ASSERT_TRUE(entry->descriptor() != NULL);
  EXPECT_STREQ("Add-Root-CA", entry->descriptor()->GetTypeName());
  EXPECT_EQ(1, entry->descriptor()->GetVersion());
  EXPECT_EQ("...", entry->ca_cert());
  EXPECT_EQ(42U, entry->sn());
  EXPECT_EQ("...", entry->signature());
  EXPECT_EQ(0U, entry->tid());
  EXPECT_EQ(1342885825U, entry->timestamp());
}

}  // namespace sk
