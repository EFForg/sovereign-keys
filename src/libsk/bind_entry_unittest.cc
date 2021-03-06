// Copyright 2012 the SK authors. All rights reserved.

#include "bind_entry.h"

#include <string>
#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "descriptor.h"
#include "slice.h"

using std::string;
using std::unique_ptr;
using std::vector;

namespace sk {

TEST(BindEntryTest, Getters) {
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

TEST(BindEntryTest, Setters) {
  unique_ptr<BindEntry> entry(new BindEntry(1));
  entry->set_ca_cert_chain("...");
  entry->set_includes_subdomains(false);
  entry->set_key("...");
  entry->set_key_type(KeyTypeValue::ECC);
  entry->set_name("foo.example.com");
  entry->set_rebinder_names({"bar.example.com", "baz.example.com"});
  entry->set_sk_signature("...");
  entry->set_sn(42);
  entry->set_services(vector<Service>({{"https", "", {}}}));
  entry->set_signature("...");
  entry->set_tid(0);
  entry->set_timestamp(1342885825);
  string out;
  entry->AppendText(&out);
  EXPECT_EQ(
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
    "\n",
    out);
}

}  // namespace sk
