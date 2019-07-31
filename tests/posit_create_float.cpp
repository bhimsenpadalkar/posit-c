#include<iostream>
#include "../src/Posit.h"
#include "Utils.h"
using namespace std;

void shouldReturnZeroForTheNumberZeroAsAPosit() {
    Posit *num = Utils::createPositByUint(8, 0, 0x00);
    ASSERT(num->toFloat(), 0);
}

void shouldReturnInfiniteForTheNumberInfiniteAsAPosit() {
    Posit *num = Utils::createPositByUint(8, 0, 0x80);

    union FloatRep {
        float floatValue;
        uint32_t binaryValue;
    };

    FloatRep inf = FloatRep{};
    inf.floatValue = num->toFloat();
    ASSERT(inf.binaryValue, 0x7F800000);
}

void shouldReturnOneForThePositNumberOne() {
    Posit *num = Utils::createPositByUint(8, 1, 0x40);
    ASSERT(num->toFloat(), 1);
}


void shouldConvertPositivePositValueIntoFloat() {
    Posit *num = Utils::createPositByUint(16, 1, 0x770E);
    ASSERT(num->toFloat(), 56.4375);
}

void shouldConvertPositValueIntoFloatForSmallPositivePositWhenNoExponentBits() {
    Posit *num = Utils::createPositByUint(8, 0, 0x20);
    ASSERT(num->toFloat(), 0.5);
}

void shouldConvertPositValueIntoFloatForSmallNegativePositWhenNoExponentBits() {
    Posit *num = Utils::createPositByUint(8, 0, 0xE0);
    ASSERT(num->toFloat(), -0.5);
}


void shouldConvertNegativePositValueIntoFloat() {
    Posit *num = Utils::createPositByUint(16, 1, 0xAA00);
    ASSERT(num->toFloat(), -2.75);
}

void shouldConvert64BitPositIntoFloat(){
    Posit *num = Utils::createPositByUint(64, 35, 0x4000000006000000);
    ASSERT(num->toFloat(), 3);
}

int main() {
    shouldReturnZeroForTheNumberZeroAsAPosit();
    shouldReturnInfiniteForTheNumberInfiniteAsAPosit();
    shouldReturnOneForThePositNumberOne();
    shouldConvertPositivePositValueIntoFloat();
    shouldConvertPositValueIntoFloatForSmallPositivePositWhenNoExponentBits();
    shouldConvertPositValueIntoFloatForSmallNegativePositWhenNoExponentBits();
    shouldConvertNegativePositValueIntoFloat();
    shouldConvert64BitPositIntoFloat();
    return 0;
}