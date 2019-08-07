#include<iostream>
#include "Posit.h"
#include "Utils.h"
#include "gtest/gtest.h"
using namespace std;

TEST(Posit_to_double,shouldConvertPositValueIntoDoubleForSmallPositivePositWhenNoExponentBits){
    Posit *num = Utils::createPositByUint(8, 0, 0x20);
    ASSERT_EQ(num->toDouble(),0.5);
}

TEST(Posit_to_double,shouldConvertPositValueIntoDoubleForSmallNegativePositWhenNoExponentBits) {
    Posit *num = Utils::createPositByUint(8, 0, 0xE0);
    ASSERT_EQ(num->toDouble(), -0.5);
}

TEST(Posit_to_double,shouldConvertPositivePositValueIntoDouble) {
    Posit *num = Utils::createPositByUint(16, 1, 0x770E);
    ASSERT_EQ(num->toDouble(), 56.4375);
}

TEST(Posit_to_double,shouldConvertNegativePositValueIntoDouble) {
    Posit *num = Utils::createPositByUint(16, 1, 0xAA00);
    ASSERT_EQ(num->toDouble(), -2.75);
}

TEST(Posit_to_double,shouldGiveZeroRepresentationOfPositToDouble) {
    Posit *num = Utils::createPositByUint(8, 0, 0x00);
    ASSERT_EQ(num->toDouble(), 0);
}

TEST(Posit_to_double,shouldGiveInfiniteRepresentationOfPositToDouble) {
    Posit *num = Utils::createPositByUint(8, 0, 0x80);

    union DoubleRep {
        double doubleValue;
        uint64_t binaryValue;
    };
    DoubleRep inf = DoubleRep{};
    inf.doubleValue = num->toDouble();
    ASSERT_EQ(inf.binaryValue, 0x7FF0000000000000);
}