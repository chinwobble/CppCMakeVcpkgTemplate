
TEST(PackTests, Teqi) {
  __m128i a = _mm_set_epi32(-61000, 1000, 2000, 3000);
  __m128i b = _mm_set_epi32(3, 2, 1, 0);
  // saturated signed pack
  // pack 4x32 bit into 8x16 bit
  // https://www.felixcloutier.com/x86/packsswb:packssdw
  __m128i result = _mm_packs_epi32(a, b);
  short resultArray[]{0, 0, 0, 0, 0, 0, 0, 0};
  _mm_storeu_si128((__m128i*)resultArray, result);
  EXPECT_EQ(resultArray[0], 3000);
  EXPECT_EQ(resultArray[1], 2000);
  EXPECT_EQ(resultArray[2], 1000);
  EXPECT_EQ(resultArray[3], -32768);
  EXPECT_EQ(resultArray[4], 0);
  EXPECT_EQ(resultArray[5], 1);
  EXPECT_EQ(resultArray[6], 2);
  EXPECT_EQ(resultArray[7], 3);
}