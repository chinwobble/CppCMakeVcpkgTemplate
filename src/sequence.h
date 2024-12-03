#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <hwy/highway.h>

namespace hn = hwy::HWY_NAMESPACE;
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

public:
    string*  mStr;
};
#endif
