#include<iostream>
#include "Posit.h"
#include "Utils.h"
#include "gtest/gtest.h"

using namespace std;

TEST(Posit_to_float, shouldReturnZeroForTheNumberZeroAsAPosit) {
    Posit *num = Utils::createPositByUint(8, 0, 0x00);
    ASSERT(num->toFloat(), 0);
}

TEST(Posit_to_float, shouldReturnInfiniteForTheNumberInfiniteAsAPosit) {
    Posit *num = Utils::createPositByUint(8, 0, 0x80);

    union FloatRep {
        float floatValue;
        uint32_t binaryValue;
    };

    FloatRep inf = FloatRep{};
    inf.floatValue = num->toFloat();
    ASSERT(inf.binaryValue, 0x7F800000);
}

TEST(Posit_to_float, shouldReturnOneForThePositNumberOne) {
    Posit *num = Utils::createPositByUint(8, 1, 0x40);
    ASSERT(num->toFloat(), 1);
}


TEST(Posit_to_float, shouldConvertPositivePositValueIntoFloat) {
    Posit *num = Utils::createPositByUint(16, 1, 0x770E);
    ASSERT(num->toFloat(), 56.4375);
}

TEST(Posit_to_float, shouldConvertPositValueIntoFloatForSmallPositivePositWhenNoExponentBits) {
    Posit *num = Utils::createPositByUint(8, 0, 0x20);
    ASSERT(num->toFloat(), 0.5);
}

TEST(Posit_to_float, shouldConvertPositValueIntoFloatForSmallNegativePositWhenNoExponentBits) {
    Posit *num = Utils::createPositByUint(8, 0, 0xE0);
    ASSERT(num->toFloat(), -0.5);
}


TEST(Posit_to_float, shouldConvertNegativePositValueIntoFloat) {
    Posit *num = Utils::createPositByUint(16, 1, 0xAA00);
    ASSERT(num->toFloat(), -2.75);
}

TEST(Posit_to_float, shouldConvert64BitPositIntoFloat) {
    Posit *num = Utils::createPositByUint(64, 35, 0x4000000006000000);
    ASSERT(num->toFloat(), 3);
}