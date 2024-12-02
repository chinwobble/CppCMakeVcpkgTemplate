#include "sequence.h"
#include <iostream>
#include <hwy/contrib/algo/transform-inl.h>

namespace hn = hwy::HWY_NAMESPACE;

Sequence::Sequence(){
}

Sequence::Sequence(string* seq){
    mStr = seq;
}

Sequence::~Sequence(){
    if(mStr)
        delete mStr;
}

void Sequence::print(){
    std::cerr << *mStr;
}

int Sequence::length(){
    return mStr->length();
}

string Sequence::reverseComplement(string* origin) {
    string str(origin->length(), 0);
    int len = origin->length();
    for(int c=0;c<origin->length();c++){
        char base = (*origin)[c];
        switch(base){
            case 'A':
            case 'a':
                str[len-c-1] = 'T';
                break;
            case 'T':
            case 't':
                str[len-c-1] = 'A';
                break;
            case 'C':
            case 'c':
                str[len-c-1] = 'G';
                break;
            case 'G':
            case 'g':
                str[len-c-1] = 'C';
                break;
            default:
                str[len-c-1] = 'N';
        }
    }
    return str;
}

string Sequence::reverseComplementHwy(string *origin)
{
    auto length = origin->length();
    const auto sequence = reinterpret_cast<const uint8_t*>(&origin[0]);
    uint8_t output[length];
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

    const hn::ScalableTag<uint8_t> d;
    hn::Transform1(d, output, length, sequence, transform);

    auto retVal = reinterpret_cast<char *>(output);
    std::string reversed(retVal, length);
    return reversed;
}

void Sequence::ReverseComplement(const uint8_t *HWY_RESTRICT sequence, const size_t size, uint8_t *HWY_RESTRICT output_array)
{
    const hn::ScalableTag<uint8_t> d;
    const hn::ScalableTag<int> d1;
    const auto lanes = hn::Lanes(d);
    // A = 65
    // T = 84
    // C = 67
    // G = 71
    // hn::Set(d, 19UL);

    const auto a = hn::Set(d, 65UL);
    const auto t = hn::Set(d, 84UL);
    // const auto c = hn::Set(d, 67UL);
    // const auto g = hn::Set(d, 71UL);
    for (size_t i = 0; i < size; i += lanes)
    {
        const auto sub_sequence = hn::Load(d, sequence + i);

        auto output = hn::Set(d, 0UL);

        output = hn::IfThenElse(hn::Eq(sub_sequence, a), t, output);
        output = hn::IfThenElse(hn::Eq(sub_sequence, t), a, output);
        // output = hn::IfThenElse(hn::Eq(sub_sequence, c), g, output);
        // output = hn::IfThenElse(hn::Eq(sub_sequence, g), c, output);
        hn::Store(output, d, output_array + i);
    }
}

Sequence Sequence::reverseComplement() {
    string* reversed = new string(Sequence::reverseComplement(mStr));
    return Sequence(reversed);
}

Sequence Sequence::operator~(){
    return reverseComplement();
}
