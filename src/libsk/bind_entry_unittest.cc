#include "bind_entry.h"

#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "descriptor.h"
#include "log_entry.h"
#include "slice.h"

using std::string;
using std::unique_ptr;

namespace sk {

TEST(BindEntryTest, Accessors) {
  unique_ptr<BindEntry> entry(BindEntry::ParseText(
    "Bind: 1\n"
    "CA-Cert-Chain: Li4u\n"
    "Includes-Subdomains: 0\n"
    "Key: Li4u\n"
    "Key-Type: ECC\n"
    "Name: foo.example.com\n"
    "Rebinder-Names: bar.example.com,baz.example.com\n"
    "SK-Signature: Li4u\n"
    "SN: 42\n"
    "Services: https\n"
    "Signature: Li4u\n"
    "TID: 0\n"
    "Timestamp: 1342885825\n"
    "\n"));
  ASSERT_TRUE(entry.get() != NULL);
  ASSERT_TRUE(entry->descriptor() != NULL);
  EXPECT_STREQ("Bind", entry->descriptor()->GetTypeName());
  EXPECT_EQ(1, entry->descriptor()->GetVersion());
  EXPECT_EQ("...", entry->ca_cert_chain());
  EXPECT_FALSE(entry->includes_subdomains());
  EXPECT_EQ("...", entry->key());
  EXPECT_EQ(KeyTypeValue::ECC, entry->key_type());
  EXPECT_EQ("foo.example.com", entry->name());
  EXPECT_EQ(2U, entry->rebinder_names().size());
  EXPECT_EQ("bar.example.com", entry->rebinder_names()[0]);
  EXPECT_EQ("baz.example.com", entry->rebinder_names()[1]);
  EXPECT_EQ("...", entry->sk_signature());
  EXPECT_EQ(42U, entry->sn());
  EXPECT_EQ(1U, entry->services().size());
  EXPECT_EQ("https", entry->services()[0].name);
  EXPECT_EQ("", entry->services()[0].port);
  EXPECT_EQ(0U, entry->services()[0].alternate_routes.size());
  EXPECT_EQ("...", entry->signature());
  EXPECT_EQ(0U, entry->tid());
  EXPECT_EQ(1342885825U, entry->timestamp());
}

}  // namespace sk
