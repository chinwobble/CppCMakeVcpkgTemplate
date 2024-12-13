
TEST(shiftTests, Teqi) {
  __m128i a = _mm_set_epi32(3, 2, 1, 0);
  // slide the vector 4 bytes
  // slide left logical immediate
  // https://www.felixcloutier.com/x86/pslldq
  __m128i result = _mm_slli_si128(a, 4);
  int resultArray[]{0, 0, 0, 0};
  _mm_storeu_si128((__m128i*)resultArray, result);
  EXPECT_EQ(resultArray[0], 0);
  EXPECT_EQ(resultArray[1], 0);
  EXPECT_EQ(resultArray[2], 1);
  EXPECT_EQ(resultArray[3], 2);
}