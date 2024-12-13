// test.cpp

TEST(AddTests, Teqi) {
  __m128i a = _mm_set_epi32(3, 2, 1, 0);
  __m128i b = _mm_set_epi32(1, 1, 1, 1);
  __m128i result = _mm_add_epi32(a, b);
  int resultArray[]{0, 0, 0, 0};
  _mm_storeu_si128((__m128i*)resultArray, result);
  EXPECT_EQ(resultArray[0], 1);
  EXPECT_EQ(resultArray[1], 2);
  EXPECT_EQ(resultArray[2], 3);
  EXPECT_EQ(resultArray[3], 4);
}