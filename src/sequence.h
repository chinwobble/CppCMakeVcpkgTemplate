#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <hwy/highway.h>

using namespace std;

class Sequence{
public:
    Sequence();
    Sequence(string*  seq);
    ~Sequence();
    void print();
    int length();
    Sequence reverseComplement();

    Sequence operator~();

    static string reverseComplement(string* origin);
    static string reverseComplementHwy(string* origin);

private:
    static void ReverseComplement(
            const uint8_t *HWY_RESTRICT sequence,
            const size_t size,
            uint8_t *HWY_RESTRICT output_array);
public:
    string*  mStr;
};

#endif
