#include<iostream>
#include "Posit.h"
#include "Utils.h"
#include "gtest/gtest.h"
using namespace std;

TEST(Posit_Create,shouldConvertFloatToPositWithLessPrecision_8) {
    Posit *num = Utils::createPositByFloat(8, 0, 4.625);

    ASSERT_EQ(num->getBinaryFormat(), 0x71);
}

TEST(Posit_Create,shouldConvertFloatToPositWithLessPrecision_10) {
    Posit *num = Utils::createPositByFloat(10, 0, 4.625);

    ASSERT_EQ(num->getBinaryFormat(), 0x1C5);
}

TEST(Posit_Create,shouldConvertFloatToPositWithExponent) {
    Posit *num = Utils::createPositByFloat(8, 2, 0.009765625);

    ASSERT_EQ(num->getBinaryFormat(), 0x15);
}

TEST(Posit_Create,shouldConvertNegativeFloatToPositWithExponent) {
    Posit *num = Utils::createPositByFloat(8, 2, -0.009765625);

    ASSERT_EQ(num->getBinaryFormat(), -0x15);
}

TEST(Posit_Create,shouldNotHavingExponentWhileTheRegimeBitsAreMore) {
    Posit *num = Utils::createPositByFloat(8, 1, 2048.2);

    ASSERT_EQ(num->getBinaryFormat(), 0x7E);
}

TEST(Posit_Create,shouldNotHavingFractionWhileTheRegimeBitsAndExponentAreMore) {
    Posit *num = Utils::createPositByFloat(8, 1, 512.9);

    ASSERT_EQ(num->getBinaryFormat(), 0x7D);
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

TEST(Posit_Create,shouldNotHavingFractionOrExponentWhileTheRegimeBitsAreMore1) {
    Posit *num = Utils::createPositByFloat(8, 1, 4096);

    ASSERT_EQ(num->getBinaryFormat(), 0x7F);
}


TEST(Posit_Create,shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore) {
    Posit *num = Utils::createPositByFloat(8, 2, 262144.3);

    ASSERT_EQ(num->getBinaryFormat(), 0x7D);
}

TEST(Posit_Create,shouldHaveLessExponentBitsAndNoFractionBitsWhileTheRegimeBitsAreMore1) {
    Posit *num = Utils::createPositByFloat(8, 3, 302365697638.4);

    ASSERT_EQ(num->getBinaryFormat(), 0x7D);
}