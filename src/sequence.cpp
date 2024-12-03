#include "sequence.h"
#include <iostream>
#include <hwy/contrib/algo/transform-inl.h>
#include <hwy/aligned_allocator.h>

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
    auto output = new uint8_t[length];
    const auto transform = [](const auto d, auto output, const auto sequence) HWY_ATTR
    {
        const auto a = hn::Set(d, 'A');
        const auto t = hn::Set(d, 'T');
        const auto c = hn::Set(d, 'C');
        const auto g = hn::Set(d, 'G');
        output = hn::IfThenElse(hn::Eq(sequence, a), t, output);
        output = hn::IfThenElse(hn::Eq(sequence, t), a, output);
        output = hn::IfThenElse(hn::Eq(sequence, c), g, output);
        output = hn::IfThenElse(hn::Eq(sequence, g), c, output);
        return output;
    };

    const hn::ScalableTag<uint8_t> d;
    Transform1(d, output, length, sequence, transform);

    auto retVal = reinterpret_cast<char *>(output);
    std::string reversed(retVal, length);
    return reversed;
}

Sequence Sequence::reverseComplement() {
    string* reversed = new string(Sequence::reverseComplement(mStr));
    return Sequence(reversed);
}

Sequence Sequence::operator~(){
    return reverseComplement();
}
