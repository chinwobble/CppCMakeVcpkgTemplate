
#include <bitset>
// https://www.felixcloutier.com/x86/pmovmskb
TEST(compare, zero) {

    __m128i a = _mm_set_epi8(
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, '\\'
    );
    __m128i backslashes = _mm_set1_epi8('\\');
    int structural_bitmap = _mm_movemask_epi8(
        _mm_cmpeq_epi8(a, backslashes)
    );
    std::bitset<8> bits{structural_bitmap};
    EXPECT_EQ(structural_bitmap, 0b00000001);
    EXPECT_EQ(bits.count(), 1);
}


TEST(compare, matching) {

    __m128i a = _mm_set_epi8(
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, '\\', '\\', '\\'
    );
    __m128i backslashes = _mm_set1_epi8('\\');
    int structural_bitmap = _mm_movemask_epi8(
        _mm_cmpeq_epi8(a, backslashes)
    );

    uint8_t shifted_bitmap = structural_bitmap << 1;
    std::bitset<8> bits{structural_bitmap};
    EXPECT_EQ(structural_bitmap, 0b00000111);
    EXPECT_EQ(shifted_bitmap, 0b00001110);
    EXPECT_EQ(~shifted_bitmap, 0xFFFFFFF1);
    EXPECT_EQ(structural_bitmap & ~ (structural_bitmap << 1), 0x1);

    EXPECT_EQ(bits.count(), 3);
}
