// main function!
int main() {
  // 00000000
  // 00001111 1 + 2 + 4 + 8
  // 00000001 1
  // 00000010 2
  // 00000100 4
  // 00001000 8
  // 00010000 16
  // 00100000 32
  // 01000000 64
  // 10000000 128
  // char a = 'A' << 1;
  // __m128i a = __m
  __m128i a =
      _mm_set_epi8(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  __m128i b = _mm_set_epi8(0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 7, 6,
                           5, 4, 3, 2, 1, 0);
  char aa = -24;
  std::array<int, 3>{1, 2, 3};
  // 0x8080
  // Perform the shuffle
  // __m128i result = _mm_shuffle_epi8(a, b);

  // // Store the result in an array (assuming you have a 16-byte array)
  char output[16];
  _mm_storeu_si128((__m128i*)output, b);

  // Print the results (optional)
  for (int i = 0; i < 16; i++) {
    fmt::print("{} ", output[i]);
    // printf("%d ", output[i]);
  }
  fmt::println("");
  return 0;
}
