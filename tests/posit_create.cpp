#include<iostream>
#include "../src/Posit.h"

using namespace std;

#define ASSERT(a, b) if(a != b) throw std::runtime_error("Failed")

Posit *createPosit(uint8_t totalBits, uint8_t exponentBits, float value) {
    Posit *num = new Posit(totalBits, exponentBits);
    num->setFloatValue(value);

    return num;
}

void shouldConvertFloatToPositWithLessPrecision_8() {
    Posit *num = createPosit(8, 0, 4.625);

    ASSERT(num->getBinaryFormat(), 0x71);
}

void shouldConvertFloatToPositWithLessPrecision_10() {
    Posit *num = createPosit(10, 0, 4.625);

    ASSERT(num->getBinaryFormat(), 0x1C5);
}

void shouldConvertFloatToPositWithExponent() {
    Posit *num = createPosit(8, 2, 0.009765625);

    ASSERT(num->getBinaryFormat(), 0x15);
}

void shouldConvertNegativeFloatToPositWithExponent() {
    Posit *num = createPosit(8, 2, -0.009765625);

    ASSERT(num->getBinaryFormat(), -0x15);
}

void shouldNotHavingExponentWhileTheRegimeBitsAreMore() {
    Posit *num = createPosit(8, 1, 2048.2);

    ASSERT(num->getBinaryFormat(), 0x7E);
}

void shouldNotHavingFractionWhileTheRegimeBitsAndExponentAreMore() {
    Posit *num = createPosit(8, 1, 512.9);

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

void shouldNotHavingFractionOrExponentWhileTheRegimeBitsAreMore1() {
    Posit *num = createPosit(8, 1, 4096);

    ASSERT(num->getBinaryFormat(), 0x7F);
}


void shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore() {
    Posit *num = createPosit(8, 2, 262144.3);

    ASSERT(num->getBinaryFormat(), 0x7D);
}

void shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore1() {
    Posit *num = createPosit(8, 3, 302365697638.4);

    ASSERT(num->getBinaryFormat(), 0x7D);
}

int main() {
    shouldConvertFloatToPositWithLessPrecision_8();
    shouldConvertFloatToPositWithLessPrecision_10();
    shouldConvertFloatToPositWithExponent();
    shouldConvertNegativeFloatToPositWithExponent();
    shouldNotHavingFractionWhileTheRegimeBitsAndExponentAreMore();

    shouldNotHavingExponentWhileTheRegimeBitsAreMore();
    shouldNotHavingFractionOrExponentWhileTheRegimeBitsAreMore1();
    shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore();
    shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore1();
    return 0;
}