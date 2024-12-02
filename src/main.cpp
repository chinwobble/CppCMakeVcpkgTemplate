// main.cpp
#include <sqlite3.h>
#include <cstdio>
#include <array>
#include <fmt/core.h>
#include <hwy/highway.h>
#include <hwy/aligned_allocator.h>
#include <hwy/contrib/algo/transform-inl.h>
HWY_BEFORE_NAMESPACE(); // at file scope
namespace hn = hwy::HWY_NAMESPACE;
namespace project
{ // optional
    namespace HWY_NAMESPACE
    {
        using namespace hwy::HWY_NAMESPACE;
        void ReverseWithTransform(
            const uint8_t *HWY_RESTRICT sequence,
            const size_t size
        ) {
            const auto transform = [](const auto d, auto output, const auto sequence) HWY_ATTR
            {
                const auto a = hn::Set(d, 65UL);
                const auto t = hn::Set(d, 84UL);
                const auto c = hn::Set(d, 67UL);
                const auto g = hn::Set(d, 71UL);
                output = hn::IfThenElse(hn::Eq(sequence, a), t, output);
                output = hn::IfThenElse(hn::Eq(sequence, t), a, output);
                output = hn::IfThenElse(hn::Eq(sequence, c), g, output);
                output = hn::IfThenElse(hn::Eq(sequence, g), c, output);
                return output;
            };
            uint8_t* output = new uint8_t[size];

            const hn::ScalableTag<uint8_t> d;
            Transform1(d, output, size, sequence, transform);

            auto reversed = std::string(reinterpret_cast<char *>(output), size);
        }
        void ReverseComplement(
            const uint8_t *HWY_RESTRICT sequence,
            const size_t size,
            uint8_t *HWY_RESTRICT output_array)
        {
            const hn::ScalableTag<uint8_t> d;
            const auto lanes = hn::Lanes(d);

            // A = 65
            // T = 84
            // C = 67
            // G = 71
            // hn::Set(d, 19UL);
            const auto a = hn::Set(d, 65UL);
            const auto t = hn::Set(d, 84UL);
            const auto c = hn::Set(d, 67UL);
            const auto g = hn::Set(d, 71UL);

            for (size_t i = 0; i < size; i += lanes)
            {
                const auto sub_sequence = hn::Load(d, sequence + i);
                auto output = hn::Set(d, 0UL);
                output = hn::IfThenElse(hn::Eq(sub_sequence, a), t, output);
                output = hn::IfThenElse(hn::Eq(sub_sequence, t), a, output);
                output = hn::IfThenElse(hn::Eq(sub_sequence, c), g, output);
                output = hn::IfThenElse(hn::Eq(sub_sequence, g), c, output);
                hn::Store(output, d, output_array + i);
            }
        }

        // implementation
        void double_int()
        {
            constexpr size_t size = 63;
            // A = 65
            // T = 84
            // C = 67
            // G = 71
            std::array<uint8_t, size> sequence{65, 65, 65, 65};
            std::array<uint8_t, size> complement{19, 19, 19, 19};
            std::array<uint8_t, size> x_array;
            // ReverseComplement(sequence.data(), size, x_array.data());
            // auto reversed = std::string(reinterpret_cast<char *>(x_array.data()), size);
        }

        // NOLINTNEXTLINE(google-readability-namespace-comments)
    } // namespace HWY_NAMESPACE
} // namespace project - optional
HWY_AFTER_NAMESPACE();
int main()
{

    project::HWY_NAMESPACE::double_int();
    // auto d = hn::ScalableTag<uint8_t>();
    // size_t N = hn::Lanes(d);
    return 0;
}