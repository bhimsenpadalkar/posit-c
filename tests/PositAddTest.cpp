#include "Posit.h"
#include "Utils.h"
#include "gtest/gtest.h"

using namespace std;

void verifyAdditionOfPosits(Posit *posit1, Posit *posit2, Posit *expectedPosit) {
    Posit *actualPosit = posit1->add(posit2);
    Utils::verifyPosits(expectedPosit, actualPosit);
}

void test(uint8_t totalBits, uint8_t exponentBits, uint64_t positValue1, uint64_t positValue2, uint64_t result){
    Posit *posit1 = Utils::createPositByUint( totalBits,exponentBits,positValue1);
    Posit *posit2 = Utils::createPositByUint(totalBits,exponentBits,positValue2);

    Posit *expectedPosit = Utils::createPositByUint(totalBits,exponentBits,result);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnZeroPositWhenTwoPositsAreAdded) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x0);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x0);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAnotherPositValueWhenTheCurrentPositIsZero) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x40);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnCurrentPositValueWhenTheAnotherPositValueIsZero) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x40);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x0);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnInfinityWhenTheCurrentValueIsInfinity) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x80);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x01);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x80);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnInfinityWhenTheAnotherPositValueIsInfinity) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x10);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x80);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x80);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAddedValueWhenBothExponentsAndSignsAreEqual) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x6C);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x62);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x73);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAddedValueWhenBothExponentAndSignsAreEqual1) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x6D);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x6A);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x75);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAddedValueWhenBothExponentAndSignsAreEqual2) {
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x5D);
    Posit *posit2 = Utils::createPositByUint(8, 1, 0x5B);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x66);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAddedValueWhenBothExponentsAreNotEqualButSignIsPositive) {
    Posit *posit1 = Utils::createPositByUint(16, 1, 0x6D00);
    Posit *posit2 = Utils::createPositByUint(16, 1, 0x5B00);

    Posit *expectedPosit = Utils::createPositByUint(16, 1, 0x7018);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAddedValueWhenBothExponentsAreNotEqualAndAreNegative) {
    Posit *posit1 = Utils::createPositByUint(16, 0, 0x1800);
    Posit *posit2 = Utils::createPositByUint(16, 0, 0x6E00);

    Posit *expectedPosit = Utils::createPositByUint(16, 0, 0x7040);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAddedValueOfNegativeExponentWhenBothAreNegativeExponents) {
    Posit *posit1 = Utils::createPositByUint(16, 0, 0x1800);
    Posit *posit2 = Utils::createPositByUint(16, 0, 0x6E00);

    Posit *expectedPosit = Utils::createPositByUint(16, 0, 0x7040);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnSecondNumberConvertedIntoFirstNumberConstraintsWhenFirstNumberIsZero) {
    Posit *posit1 = Utils::createPositByUint(8, 3, 0x00);
    Posit *posit2 = Utils::createPositByUint(16, 1, 0x5AD8);

    Posit *expectedPosit = Utils::createPositByUint(8, 3, 0x46);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnInfinityInTheFirstNumberFormatWhenTheSecondNumberIsInfinity) {
    Posit *posit1 = Utils::createPositByUint(16, 1, 0x5AD8);
    Posit *posit2 = Utils::createPositByUint(8, 2, 0x80);

    Posit *expectedPosit = Utils::createPositByUint(16, 1, 0x8000);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add,
     shouldReturnSecondNumberAsNegativeWhenFirstNumberIsInfinityAndSecondNumberIsNegativeAndSameExponentBits) {
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x00);
    Posit *posit2 = Utils::createPositByUint(16, 1, 0x9D00);

    Posit *expectedPosit = Utils::createPositByUint(8, 1, 0x9D);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnInfinityWhenExponentBitsAreNotEqualAndTotalBitsAreLess) {
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x00);
    Posit *posit2 = Utils::createPositByUint(16, 0, 0x9D00);

    Posit *expectedPosit = Utils::createPositByUint(8, 1, 0xAD);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnInfinityWhenExponentBitsAreNotEqualAndTotalBitsAreMore) {
    Posit *posit1 = Utils::createPositByUint(16, 1, 0x0000);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x9D);

    Posit *expectedPosit = Utils::createPositByUint(16, 1, 0xAD00);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnZeroWhenTwoDifferentSignsOfSameValueOfSameSize) {
    Posit *posit1 = Utils::createPositByUint(8, 0, -0x9D);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x9D);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x00);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnZeroWhenTwoDifferentSignsOfSameValueOfDifferentSize) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x9D);
    Posit *posit2 = Utils::createPositByUint(16, 2, -0xB680);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x00);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnTheSubtractedValueWhenFirstOneIsGreaterAndPositive) {
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x54);
    Posit *posit2 = Utils::createPositByUint(8, 1, 0xBE);

    Posit *expectedPosit = Utils::createPositByUint(8, 1, 0x46);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnTheSubtractedValueWhenFirstOneIsLesserAndPositive) {
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x42);
    Posit *posit2 = Utils::createPositByUint(8, 1, 0xAC);

    Posit *expectedPosit = Utils::createPositByUint(8, 1, 0xBA);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}


TEST(Posit_add, shouldReturnTheSubtractedValueWhenFirstOneIsGreaterAndPositive1) {
    Posit *posit1 = Utils::createPositByUint(16, 2, 0x64AF);
    Posit *posit2 = Utils::createPositByUint(16, 2, -0x50BC);

    Posit *expectedPosit = Utils::createPositByUint(16, 2, 0x6423);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnTheSubtractedValueWhenFirstOneIsLesserAndNegative1) {
    Posit *posit1 = Utils::createPositByUint(16, 2, -0x50BC);
    Posit *posit2 = Utils::createPositByUint(16, 2, 0x64AF);

    Posit *expectedPosit = Utils::createPositByUint(16, 2, 0x6423);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnTheSubtractedValueWhenFirstOneIsGreaterAndNegative) {
    Posit *posit1 = Utils::createPositByUint(16, 2, -0x64AF);
    Posit *posit2 = Utils::createPositByUint(16, 2, 0x50BC);

    Posit *expectedPosit = Utils::createPositByUint(16, 2, -0x6423);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnAddedValueWhenBothExponentAndSignsAreEqual0) {
    Posit *posit1 = Utils::createPositByUint(8,0,0x94);
    Posit *posit2 = Utils::createPositByUint(8,0,0x9E);
    Posit *expectedPosit = Utils::createPositByUint(8,0,0x8D);

    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnTheSubtractedValueWhenFirstOneIsGreaterAndPositiveWithSameExponentBitsAndTotalBits0) {
    Posit *posit1 = Utils::createPositByUint(8,1, 0x54);
    Posit *posit2 = Utils::createPositByUint(8,1, 0xBE);
    Posit *expectedPosit = Utils::createPositByUint(8,0,0x46);

    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

TEST(Posit_add, shouldReturnZeroWhenBothValuesAreEqualHavingDifferentSigns0) {
    test(8, 0, 0x9D, 0x63, 0x00);
    test(8, 1, 0x9D, 0x63, 0x00);
    test(8, 2, 0x9D, 0x63, 0x00);
}

TEST(Posit_add, shouldReturnTheSubtractedValueWhenFirstOneIsGreaterAndNegative0 ) {
    test(16, 2, 0x9B51, 0x50BC, 0x9BDD);
}

TEST(Posit_add, shouldReturnInfiniteWhenTheExponentAreAtMax0 ){
    test(8, 0, 0x7F, 0x7F, 0x80);
}