#include <bitset>
// https://www.felixcloutier.com/x86/pmovmskb
TEST(Movemask, zero) {

    __m128i a = _mm_set_epi8(
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    );

    int result = _mm_movemask_epi8(a);

    uint64_t mask = 0x0;
    std::bitset<16> bits{mask};
    EXPECT_EQ(bits.count(), 0);
    EXPECT_EQ(result, mask);
}

TEST(Movemask, all) {
    __m128i a = _mm_set_epi8(
        0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80
    );

    int result = _mm_movemask_epi8(a);

    uint64_t mask = 0xFFFF;
    std::bitset<16> bits{mask};
    EXPECT_EQ(bits.count(), 16);
    EXPECT_EQ(result, mask);
}

TEST(Movemask, half) {
    __m128i a = _mm_set_epi8(
        0x80, 0x80, 0x80, 0x80,
        0x80, 0x80, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    );

    int result = _mm_movemask_epi8(a);

    uint64_t mask = 0xFF00;
    std::bitset<16> bits{mask};
    EXPECT_EQ(bits.count(), 8);
    EXPECT_EQ(result, mask);
}

// https://www.felixcloutier.com/x86/pmovsx

TEST(Movemask, sign) {
    __m128i a = _mm_set_epi32(
        0, 0, -2000, 1000
    );

    __m128i result = _mm_cvtepi32_epi64(a);

    int64_t resultArray[]{0, 0};

    _mm_storeu_si128((__m128i*)resultArray, result);

    EXPECT_EQ(resultArray[0], 1000);
    EXPECT_EQ(resultArray[1], -2000);
}