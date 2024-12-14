TEST(Shuffle, noop) {
    __m128i a = _mm_set_epi32(3, 2, 1, 0);
    // __m128i b = _mm_set_epi32(
    //     // every two character is one byte
    //     // every two character
    //     0x40000004,
    //     0x40000003,
    //     0x40000002,
    //     0x40000001);
    __m128i b = _mm_set_epi32(0x0F0E0D0C, 0x0B0A0908, 0x07060504, 0x03020100);
    __m128i result = _mm_shuffle_epi8(a, b);

    int resultArray[]{0, 0, 0, 0};
    _mm_storeu_si128((__m128i*)resultArray, result);
    EXPECT_EQ(resultArray[0], 0);
    EXPECT_EQ(resultArray[1], 1);
    EXPECT_EQ(resultArray[2], 2);
    EXPECT_EQ(resultArray[3], 3);
}

TEST(Shuffle, reverse) {
    __m128i a = _mm_set_epi32(3, 2, 1, 0);
    __m128i b = _mm_set_epi32(0x03020100, 0x07060504, 0x0B0A0908, 0x0F0E0D0C);
    __m128i result = _mm_shuffle_epi8(a, b);

    int resultArray[]{0, 0, 0, 0};
    _mm_storeu_si128((__m128i*)resultArray, result);
    EXPECT_EQ(resultArray[0], 3);
    EXPECT_EQ(resultArray[1], 2);
    EXPECT_EQ(resultArray[2], 1);
    EXPECT_EQ(resultArray[3], 0);
}
