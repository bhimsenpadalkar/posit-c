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

    ASSERT(num->getBinaryFormat(), 0x1C5);
}

void shouldConvertFloatToPositWithExponent(){
    Posit *num = new Posit(8,2);
    num->setFloatValue(0.009765625);

    ASSERT(num->getBinaryFormat(), 0x15);
}

void shouldConvertNegativeFloatToPositWithExponent(){
    Posit *num = new Posit(8,2);
    num->setFloatValue(-0.009765625);

    ASSERT(num->getBinaryFormat(), -0x15);
}

void shouldNotHavingExponentWhileTheRegimeBitsAreMore(){
    Posit *num = new Posit(8,1);
    num->setFloatValue(2048.2);

    ASSERT(num->getBinaryFormat(), 0x7E);
}

void shouldNotHavingFractionWhileTheRegimeBitsAndExponentAreMore(){
    Posit *num = new Posit(8,1);
    num->setFloatValue(512.9);

    ASSERT(num->getBinaryFormat(), 0x7D);
}

/*
 * If the first bit after the sign bit is a 0,
 * then the regime bits continue until you run out of bits or encounter a 1.
 * Similarly, if the first bit after the sign bit is a 1,
 * the regime bits continue until you run out of bits or encounter a 0.
 * The bit that indicates the end of a run is not included in the regime;
 * the regime is a string of all 0’s or all 1’s.
 * https://www.johndcook.com/blog/2018/04/11/anatomy-of-a-posit-number/
 */

void shouldNotHavingFractionOrExponentWhileTheRegimeBitsAreMore1(){
    Posit *num = new Posit(8,1);
    num->setFloatValue(4096);

    ASSERT(num->getBinaryFormat(), 0x7F);
}


void shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore() {
    Posit *num = new Posit(8,2);
    num->setFloatValue(262144.3);

    ASSERT(num->getBinaryFormat(), 0x7D);
}

int main() {
    shouldConvertFloatToPositWithLessPrecision_8();
    shouldConvertFloatToPositWithLessPrecision_10();
    shouldConvertFloatToPositWithExponent();
    shouldConvertNegativeFloatToPositWithExponent();
    shouldNotHavingFractionWhileTheRegimeBitsAndExponentAreMore();

    shouldNotHavingExponentWhileTheRegimeBitsAreMore(); // changed (added 58,61)
    shouldNotHavingFractionOrExponentWhileTheRegimeBitsAreMore1(); //problem not fixed more regime bits
    shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore();//problem not fixed more exponent bits
    return 0;
}