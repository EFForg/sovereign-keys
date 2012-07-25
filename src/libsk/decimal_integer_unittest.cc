#include "decimal_integer.h"

#include <assert.h>
#include <string>

#include "gtest/gtest.h"
#include "mt_random.h"
#include "slice.h"

using std::string;

namespace sk {
namespace {
uint64_t Decode(string value) {
  uint64_t result;
  if (!ReadDecimalInteger(value, &result))
    assert(0 && "Decode failed.");
  return result;
}

string Encode(uint64_t value) {
  string out;
  AppendDecimalInteger(value, &out);
  return out;
}
}  // namespace

TEST(DecimalIntegerTest, Encode) {
  EXPECT_EQ("0", Encode(0ULL));
  EXPECT_EQ("1", Encode(1ULL));
  EXPECT_EQ("12", Encode(12ULL));
  EXPECT_EQ("123", Encode(123ULL));
  EXPECT_EQ("1234", Encode(1234ULL));
  EXPECT_EQ("12345", Encode(12345ULL));
  EXPECT_EQ("123456", Encode(123456ULL));
  EXPECT_EQ("1234567", Encode(1234567ULL));
  EXPECT_EQ("12345678", Encode(12345678ULL));
  EXPECT_EQ("123456789", Encode(123456789ULL));
  EXPECT_EQ("1234567890", Encode(1234567890ULL));
  EXPECT_EQ("12345678901", Encode(12345678901ULL));
  EXPECT_EQ("123456789012", Encode(123456789012ULL));
  EXPECT_EQ("1234567890123", Encode(1234567890123ULL));
  EXPECT_EQ("12345678901234", Encode(12345678901234ULL));
  EXPECT_EQ("123456789012345", Encode(123456789012345ULL));
  EXPECT_EQ("1234567890123456", Encode(1234567890123456ULL));
  EXPECT_EQ("12345678901234567", Encode(12345678901234567ULL));
  EXPECT_EQ("123456789012345678", Encode(123456789012345678ULL));
  EXPECT_EQ("1234567890123456789", Encode(1234567890123456789ULL));
  EXPECT_EQ("12345678901234567890", Encode(12345678901234567890ULL));
  EXPECT_EQ("10", Encode(10ULL));
  EXPECT_EQ("100", Encode(100ULL));
  EXPECT_EQ("1000", Encode(1000ULL));
}

TEST(DecimalIntegerTest, Decode) {
  EXPECT_EQ(0ULL, Decode("0"));
  EXPECT_EQ(1ULL, Decode("1"));
  EXPECT_EQ(12ULL, Decode("12"));
  EXPECT_EQ(123ULL, Decode("123"));
  EXPECT_EQ(1234ULL, Decode("1234"));
  EXPECT_EQ(12345ULL, Decode("12345"));
  EXPECT_EQ(123456ULL, Decode("123456"));
  EXPECT_EQ(1234567ULL, Decode("1234567"));
  EXPECT_EQ(12345678ULL, Decode("12345678"));
  EXPECT_EQ(123456789ULL, Decode("123456789"));
  EXPECT_EQ(1234567890ULL, Decode("1234567890"));
  EXPECT_EQ(12345678901ULL, Decode("12345678901"));
  EXPECT_EQ(123456789012ULL, Decode("123456789012"));
  EXPECT_EQ(1234567890123ULL, Decode("1234567890123"));
  EXPECT_EQ(12345678901234ULL, Decode("12345678901234"));
  EXPECT_EQ(123456789012345ULL, Decode("123456789012345"));
  EXPECT_EQ(1234567890123456ULL, Decode("1234567890123456"));
  EXPECT_EQ(12345678901234567ULL, Decode("12345678901234567"));
  EXPECT_EQ(123456789012345678ULL, Decode("123456789012345678"));
  EXPECT_EQ(1234567890123456789ULL, Decode("1234567890123456789"));
  EXPECT_EQ(12345678901234567890ULL, Decode("12345678901234567890"));
  EXPECT_EQ(10ULL, Decode("10"));
  EXPECT_EQ(100ULL, Decode("100"));
  EXPECT_EQ(1000ULL, Decode("1000"));
}

TEST(DecimalIntegerTest, DecodeErrors) {
  uint64_t unused;

  // Empty string not allowed.
  EXPECT_FALSE(ReadDecimalInteger("", &unused));

  // Leading zeros aren't allowed (except for 0).
  EXPECT_TRUE(ReadDecimalInteger("0", &unused));
  EXPECT_FALSE(ReadDecimalInteger("01", &unused));

  // Non-digits are an error.
  EXPECT_FALSE(ReadDecimalInteger("1.", &unused));
  EXPECT_FALSE(ReadDecimalInteger("-1", &unused));
  EXPECT_FALSE(ReadDecimalInteger("10;", &unused));
  EXPECT_FALSE(ReadDecimalInteger("0x10", &unused));

  // Values larger than 64 bits are an error.
  EXPECT_FALSE(ReadDecimalInteger("100000000000000000000", &unused));
  EXPECT_FALSE(ReadDecimalInteger("18446744073709551616", &unused));
}

TEST(DecimalIntegerTest, Randoms) {
  MTRandom prng;
  prng.Seed(42);
  const int kNumRandoms = 100000;
  for (int i = 0; i < kNumRandoms; i++) {
    uint64_t value = prng.GetRandom();
    EXPECT_EQ(value, Decode(Encode(value)));
  }
}

}  // namespace sk
