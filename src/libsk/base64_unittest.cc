// Copyright 2012 the SK authors. All rights reserved.

#include "base64.h"

#include <assert.h>
#include <string>

#include "gtest/gtest.h"
#include "mt_random.h"
#include "slice.h"
#include "test_util.h"

using std::string;
using sk::testing::Unhex;

namespace sk {
namespace {
// Some random data for checking that encoding/decoding are standard.
const char* kRandomData = 
  "72a5a60040bb54c90419995dd406ea7bb041e0ac69deba59bf359468bdf50b07"
  "72279c4d2d19e5da09e8c655a15e807fa70b12ce23b3235cc60681b97d81050e"
  "91f56c89652ff30126199546689444a7a0f710fe3fba37fc5b55bf4c4ccf1e64"
  "60be5b0f0d7449aaf32054d5bb8ad6366d3bc7447c378b6d3006eb9bef105edc"
  "ab5fcca8e29bfe7f177ab71fc6e8ecd14075ccd9c9a75a84846dd2636ba01ec5"
  "bcc1922ed7d8a649cea58a8bc61b9bd08dbf57a68860f4ae02764db802db43f9"
  "3b847bd7aae396db6e";

// Output from GNU base64 with substitution from / -> _, + -> -.
const char* kRandomDataGNUBase64 =
  "cqWmAEC7VMkEGZld1Abqe7BB4Kxp3rpZvzWUaL31CwdyJ5xNLRnl2gnoxlWhXoB_"
  "pwsSziOzI1zGBoG5fYEFDpH1bIllL_MBJhmVRmiURKeg9xD-P7o3_FtVv0xMzx5k"
  "YL5bDw10SarzIFTVu4rWNm07x0R8N4ttMAbrm-8QXtyrX8yo4pv-fxd6tx_G6OzR"
  "QHXM2cmnWoSEbdJja6AexbzBki7X2KZJzqWKi8Ybm9CNv1emiGD0rgJ2TbgC20P5"
  "O4R716rjlttu";

string Encode(string data) {
  string result;
  AppendBase64(data, &result);
  return result;
}

string Decode(string data) {
  string result;
  if (!ReadBase64(data, &result))
    assert(0 && "Decode failed.");
  return result;
}
}  // namespace

TEST(Base64Test, Encode) {
  // Test vectors from http://tools.ietf.org/html/rfc4648.
  EXPECT_EQ("", Encode(""));
  EXPECT_EQ("Zg==", Encode("f"));
  EXPECT_EQ("Zm8=", Encode("fo"));
  EXPECT_EQ("Zm9v", Encode("foo"));
  EXPECT_EQ("Zm9vYg==", Encode("foob"));
  EXPECT_EQ("Zm9vYmE=", Encode("fooba"));
  EXPECT_EQ("Zm9vYmFy", Encode("foobar"));
}

TEST(Base64Test, Decode) {
  // Test vectors from http://tools.ietf.org/html/rfc4648.
  EXPECT_EQ("", Decode(""));
  EXPECT_EQ("f", Decode("Zg=="));
  EXPECT_EQ("fo", Decode("Zm8="));
  EXPECT_EQ("foo", Decode("Zm9v"));
  EXPECT_EQ("foob", Decode("Zm9vYg=="));
  EXPECT_EQ("fooba", Decode("Zm9vYmE="));
  EXPECT_EQ("foobar", Decode("Zm9vYmFy"));
}

TEST(Base64Test, DecodeErrors) {
  string unused;

  // The empty string is a valid encoding.
  EXPECT_TRUE(ReadBase64("", &unused));

  // An encoded string must be a multiple of 4 bytes long.
  EXPECT_FALSE(ReadBase64("Zg", &unused));

  // Fail for invalid characters such as *.
  // Check each offset in the main decode loop and in the padding.
  EXPECT_FALSE(ReadBase64("*m9vYg==", &unused));
  EXPECT_FALSE(ReadBase64("Z*9vYg==", &unused));
  EXPECT_FALSE(ReadBase64("Zm*vYg==", &unused));
  EXPECT_FALSE(ReadBase64("Zm9*Yg==", &unused));
  EXPECT_FALSE(ReadBase64("*g==", &unused));
  EXPECT_FALSE(ReadBase64("Z*==", &unused));
  EXPECT_FALSE(ReadBase64("*m8=", &unused));
  EXPECT_FALSE(ReadBase64("Z*8=", &unused));
  EXPECT_FALSE(ReadBase64("Zm*=", &unused));

  // Only the last two bytes may be padding.
  EXPECT_FALSE(ReadBase64("=m9vYg==", &unused));
  EXPECT_FALSE(ReadBase64("Z=9vYg==", &unused));
  EXPECT_FALSE(ReadBase64("Zm=vYg==", &unused));
  EXPECT_FALSE(ReadBase64("Zm9=Yg==", &unused));
  EXPECT_FALSE(ReadBase64("=m9v", &unused));
  EXPECT_FALSE(ReadBase64("Z=9v", &unused));
  EXPECT_FALSE(ReadBase64("Zm=v", &unused));
  EXPECT_FALSE(ReadBase64("Z==v", &unused));
  EXPECT_FALSE(ReadBase64("===v", &unused));
  EXPECT_FALSE(ReadBase64("Z===", &unused));
  EXPECT_FALSE(ReadBase64("====", &unused));
}

TEST(Base64Test, Randoms) {
  const int kNumRandoms = 1000;
  const int kMaxBlockSize = 5000;
  MTRandom prng;
  prng.Seed(42);
  for (int i = 0; i < kNumRandoms; i++) {
    string data;
    const int length = prng.GetRandom() % kMaxBlockSize;
    for (int j = 0; j < length; j++)
      data.append(1, prng.GetRandom() & 255);
    EXPECT_EQ(data, Decode(Encode(data)));
  }
}

TEST(Base64Test, EncodeIsStandard) {
  string data(Unhex(kRandomData));
  EXPECT_EQ(kRandomDataGNUBase64, Encode(data));
}

TEST(Base64Test, DecodeIsStandard) {
  string data(Unhex(kRandomData));
  EXPECT_EQ(data, Decode(kRandomDataGNUBase64));
}
}  // namespace sk
