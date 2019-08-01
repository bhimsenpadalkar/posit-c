//
// Created by sai-ganesh on 31/07/19.
//
#include<iostream>

using namespace std;
#define ASSERT(a, b) if(a != b) throw std::runtime_error("Failed")

class Posit;

class Utils {
public:
    static Posit *createPositByUint(uint8_t totalBits, uint8_t exponentBits, uint64_t positValue);

    static Posit *createPositByFloat(uint8_t totalBits, uint8_t exponentBits, float floatValue);

    static void verifyPosits(Posit *posit1, Posit *posit2);
};

