#include<iostream>
#include "../src/Posit.h"

using namespace std;

#define ASSERT(a, b) if(a != b) throw std::runtime_error("Failed")

Posit *createPosit(uint8_t totalBits, uint8_t exponentBits, uint64_t positValue) {
    Posit *num = new Posit(totalBits, exponentBits);
    num->setPositValue(positValue);
    return num;
}

void shouldReturnZeroForTheNumberZeroAsAPosit() {
    Posit *num = createPosit(8, 0, 0x00);
    ASSERT(num->toFloat(), 0);
}

void shouldReturnInfiniteForTheNumberInfiniteAsAPosit() {
    Posit *num = createPosit(8, 0, 0x80);

    union FloatRep {
        float floatValue;
        uint32_t binaryValue;
    };

    FloatRep inf = FloatRep{};
    inf.floatValue = num->toFloat();
    ASSERT(inf.binaryValue, 0x7F800000);
}

void shouldReturnOneForThePositNumberOne() {
    Posit *num = createPosit(8, 1, 0x40);
    ASSERT(num->toFloat(), 1);
}


void shouldConvertPositivePositValueIntoFloat() {
    Posit *num = createPosit(16, 1, 0x770E);
    ASSERT(num->toFloat(), 56.4375);
}

void shouldConvertPositValueIntoFloatForSmallPositivePositWhenNoExponentBits() {
    Posit *num = createPosit(8, 0, 0x20);
    ASSERT(num->toDouble(), 0.5);
}

void shouldConvertPositValueIntoFloatForSmallNegativePositWhenNoExponentBits() {
    Posit *num = createPosit(8, 0, 0xE0);
    ASSERT(num->toDouble(), -0.5);
}


void shouldConvertNegativePositValueIntoFloat() {
    Posit *num = createPosit(16, 1, 0xAA00);
    ASSERT(num->toDouble(), -2.75);
}

int main() {
    shouldReturnZeroForTheNumberZeroAsAPosit();
    shouldReturnInfiniteForTheNumberInfiniteAsAPosit();
    shouldReturnOneForThePositNumberOne();
    shouldConvertPositivePositValueIntoFloat();
    shouldConvertPositValueIntoFloatForSmallPositivePositWhenNoExponentBits();
    shouldConvertPositValueIntoFloatForSmallNegativePositWhenNoExponentBits();
    shouldConvertNegativePositValueIntoFloat();
    return 0;
}