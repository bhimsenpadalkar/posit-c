#include<iostream>
#include "../src/Posit.h"
using namespace std;

#define ASSERT(a,b) if(a != b) throw std::runtime_error("Failed")

void shouldConvertFloatToPositWithLessPrecision_8(){
    Posit *num = new Posit(8,0);
    num->setFloatValue(4.625);

    ASSERT(num->getBinaryFormat(), 0x71);
}

void shouldConvertFloatToPositWithLessPrecision_10(){
    Posit *num = new Posit(10,0);
    num->setFloatValue(4.625);

    cout << num->getBinaryFormat() <<endl;
    ASSERT(num->getBinaryFormat(), 0x1C5);
}

void shouldConvertFloatToPositWithExponent(){
    Posit *num = new Posit(8,2);
    num->setFloatValue(0.009765625);
    cout << num->getBinaryFormat() << endl;
    ASSERT(num->getBinaryFormat(), 0x15);
}

void shouldConvertNegativeFloatToPositWithExponent(){
    Posit *num = new Posit(8,2);
    num->setFloatValue(-0.009765625);
    cout << num->getBinaryFormat() << endl;
    ASSERT(num->getBinaryFormat(), -0x15);
}

int main() {
    shouldConvertFloatToPositWithLessPrecision_8();
    shouldConvertFloatToPositWithLessPrecision_10();
    shouldConvertFloatToPositWithExponent();
    shouldConvertNegativeFloatToPositWithExponent();
    return 0;
}