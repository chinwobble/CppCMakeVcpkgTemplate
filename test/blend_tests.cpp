
TEST(Blend, sourceA) {
    __m128i a = _mm_set_epi32(3, 2, 1, 0);
    __m128i b = _mm_set_epi32(7, 6, 5, 4);
    __m128i mask = _mm_set_epi8(
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    );

    __m128i result = _mm_blendv_epi8(a, b, mask);
    int resultArray[]{0, 0, 0, 0};

    _mm_storeu_si128((__m128i*)resultArray, result);

    EXPECT_EQ(resultArray[0], 0);
    EXPECT_EQ(resultArray[1], 1);
    EXPECT_EQ(resultArray[2], 2);
    EXPECT_EQ(resultArray[3], 3);
}

TEST(Blend, sourceB) {
    __m128i a = _mm_set_epi32(3, 2, 1, 0);
    __m128i b = _mm_set_epi32(7, 6, 5, 4);
    __m128i mask = _mm_set_epi8(
        0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80
    );

    __m128i result = _mm_blendv_epi8(a, b, mask);
    int resultArray[]{0, 0, 0, 0};

    _mm_storeu_si128((__m128i*)resultArray, result);

    EXPECT_EQ(resultArray[0], 4);
    EXPECT_EQ(resultArray[1], 5);
    EXPECT_EQ(resultArray[2], 6);
    EXPECT_EQ(resultArray[3], 7);
}