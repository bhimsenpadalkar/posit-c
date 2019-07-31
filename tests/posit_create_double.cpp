#include<iostream>
#include "../src/Posit.h"
#include "Utils.h"
using namespace std;

void shouldConvertPositValueIntoDoubleForSmallPositivePositWhenNoExponentBits() {
    Posit *num = Utils::createPositByUint(8, 0, 0x20);
    ASSERT(num->toDouble(), 0.5);
}

void shouldConvertPositValueIntoDoubleForSmallNegativePositWhenNoExponentBits() {
    Posit *num = Utils::createPositByUint(8, 0, 0xE0);
    ASSERT(num->toDouble(), -0.5);
}

void shouldConvertPositivePositValueIntoDouble() {
    Posit *num = Utils::createPositByUint(16, 1, 0x770E);
    ASSERT(num->toDouble(), 56.4375);
}

void shouldConvertNegativePositValueIntoDouble() {
    Posit *num = Utils::createPositByUint(16, 1, 0xAA00);
    ASSERT(num->toDouble(), -2.75);
}

void shouldGiveZeroRepresentationOfPositToDouble() {
    Posit *num = Utils::createPositByUint(8, 0, 0x00);
    ASSERT(num->toDouble(), 0);
}

void shouldGiveInfiniteRepresentationOfPositToDouble() {
    Posit *num = Utils::createPositByUint(8, 0, 0x80);

    union DoubleRep {
        double doubleValue;
        uint64_t binaryValue;
    };
    DoubleRep inf = DoubleRep{};
    inf.doubleValue = num->toDouble();
    ASSERT(inf.binaryValue, 0x7FF0000000000000);
}

int main() {
    shouldConvertPositValueIntoDoubleForSmallPositivePositWhenNoExponentBits();
    shouldConvertPositValueIntoDoubleForSmallNegativePositWhenNoExponentBits();
    shouldConvertPositivePositValueIntoDouble();
    shouldConvertNegativePositValueIntoDouble();
    shouldGiveZeroRepresentationOfPositToDouble();
    shouldGiveInfiniteRepresentationOfPositToDouble();
    return 0;
}