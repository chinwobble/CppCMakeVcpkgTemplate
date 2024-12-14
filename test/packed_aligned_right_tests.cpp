

TEST(PackedAligned, noop) {
    __m128i a = _mm_set_epi32(-61000, 1000, 2000, 3000);
    __m128i b = _mm_set_epi32(3, 2, 1, 0);
    __m128i result = _mm_alignr_epi8(a, b, 0);

    int resultArray[]{0, 0, 0, 0};
    _mm_storeu_si128((__m128i*)resultArray, result);
    EXPECT_EQ(resultArray[0], 0);
    EXPECT_EQ(resultArray[1], 1);
    EXPECT_EQ(resultArray[2], 2);
    EXPECT_EQ(resultArray[3], 3);
}


TEST(PackedAligned, shift4bytes) {
    __m128i a = _mm_set_epi32(-61000, 1000, 2000, 3000);
    __m128i b = _mm_set_epi32(3, 2, 1, 0);
    __m128i result = _mm_alignr_epi8(a, b, 4);

    int resultArray[]{0, 0, 0, 0};
    _mm_storeu_si128((__m128i*)resultArray, result);
    EXPECT_EQ(resultArray[0], 1);
    EXPECT_EQ(resultArray[1], 2);
    EXPECT_EQ(resultArray[2], 3);
    EXPECT_EQ(resultArray[3], 3000);
}


TEST(PackedAligned, mask) {
    __m128i a = _mm_set_epi32(-61000, 1000, 2000, 3000);
    __m128i b = _mm_set_epi32(3, 2, 1, 0);
    // __m128i result = _mm_mask_alignr_epi8(a, b, 0);

    int resultArray[]{0, 0, 0, 0};
    // _mm_storeu_si128((__m128i*)resultArray, result);
    // EXPECT_EQ(resultArray[0], 1);
    // EXPECT_EQ(resultArray[1], 2);
    // EXPECT_EQ(resultArray[2], 3);
    // EXPECT_EQ(resultArray[3], 3000);
}