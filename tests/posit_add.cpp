#include "../src/Posit.h"
#include "Utils.h"

using namespace std;

void verifyAdditionOfPosits(Posit *posit1, Posit *posit2, Posit *expectedPosit) {
    Posit *actualPosit = posit1->add(posit2);
    Utils::verifyPosits(expectedPosit, actualPosit);
}

void shouldReturnZeroPositWhenTwoPositsAreAdded() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x0);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x0);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnAnotherPositValueWhenTheCurrentPositIsZero() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x40);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnCurrentPositValueWhenTheAnotherPositValueIsZero() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x40);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x0);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnInfinityWhenTheCurrentValueIsInfinity() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x80);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x01);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x80);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnInfinityWhenTheAnotherPositValueIsInfinity() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x10);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x80);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x80);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnAddedValueWhenBothExponentsAndSignsAreEqual() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x6C);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x62);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x73);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnAddedValueWhenBothExponentAndSignsAreEqual1() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x6D);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x6A);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x75);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnAddedValueWhenBothExponentAndSignsAreEqual2() {
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x5D);
    Posit *posit2 = Utils::createPositByUint(8, 1, 0x5B);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x66);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnAddedValueWhenBothExponentsAreNotEqualButSignIsPositive() {
    Posit *posit1 = Utils::createPositByUint(16, 1, 0x6D00);
    Posit *posit2 = Utils::createPositByUint(16, 1, 0x5B00);

    Posit *expectedPosit = Utils::createPositByUint(16, 1, 0x7018);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnAddedValueWhenBothExponentsAreNotEqualAndAreNegative() {
    Posit *posit1 = Utils::createPositByUint(16, 0, 0x1800);
    Posit *posit2 = Utils::createPositByUint(16, 0, 0x6E00);

    Posit *expectedPosit = Utils::createPositByUint(16, 0, 0x7040);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnAddedValueOfNegativeExponentWhenBothAreNegativeExponents() {
    Posit *posit1 = Utils::createPositByUint(16, 0, 0x1800);
    Posit *posit2 = Utils::createPositByUint(16, 0, 0x6E00);

    Posit *expectedPosit = Utils::createPositByUint(16, 0, 0x7040);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnSecondNumberConvertedIntoFirstNumberConstraintsWhenFirstNumberIsZero() {
    Posit *posit1 = Utils::createPositByUint(8, 3, 0x00);
    Posit *posit2 = Utils::createPositByUint(16, 1, 0x5AD8);

    Posit *expectedPosit = Utils::createPositByUint(8, 3, 0x46);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnInfinityInTheFirstNumberFormatWhenTheSecondNumberIsInfinity() {
    Posit *posit1 = Utils::createPositByUint(16, 1, 0x5AD8);
    Posit *posit2 = Utils::createPositByUint(8, 2, 0x80);

    Posit *expectedPosit = Utils::createPositByUint(16, 1, 0x8000);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnSecondNumberAsNegativeWhenFirstNumberIsInfinityAndSecondNumberIsNegativeAndSameExponentBits(){
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x00);
    Posit *posit2 = Utils::createPositByUint(16, 1, 0x9D00);

    Posit *expectedPosit = Utils::createPositByUint(8, 1, 0x9D);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnInfinityWhenExponentBitsAreNotEqualAndTotalBitsAreLess(){
    Posit *posit1 = Utils::createPositByUint(8, 1, 0x00);
    Posit *posit2 = Utils::createPositByUint(16, 0, 0x9D00);

    Posit *expectedPosit = Utils::createPositByUint(8, 1, 0xAD);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

void shouldReturnInfinityWhenExponentBitsAreNotEqualAndTotalBitsAreMore(){
    Posit *posit1 = Utils::createPositByUint(16, 1, 0x0000);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x9D);

    Posit *expectedPosit = Utils::createPositByUint(16, 1, 0xAD00);
    verifyAdditionOfPosits(posit1, posit2, expectedPosit);
}

int main() {
    shouldReturnZeroPositWhenTwoPositsAreAdded();
    shouldReturnAnotherPositValueWhenTheCurrentPositIsZero();
    shouldReturnCurrentPositValueWhenTheAnotherPositValueIsZero();
    shouldReturnInfinityWhenTheCurrentValueIsInfinity();
    shouldReturnInfinityWhenTheAnotherPositValueIsInfinity();
    shouldReturnAddedValueWhenBothExponentsAndSignsAreEqual();
    shouldReturnAddedValueWhenBothExponentAndSignsAreEqual1();
    shouldReturnAddedValueWhenBothExponentAndSignsAreEqual2();
    shouldReturnAddedValueWhenBothExponentsAreNotEqualButSignIsPositive();
    shouldReturnAddedValueWhenBothExponentsAreNotEqualAndAreNegative();
    shouldReturnAddedValueOfNegativeExponentWhenBothAreNegativeExponents();
    shouldReturnSecondNumberConvertedIntoFirstNumberConstraintsWhenFirstNumberIsZero();
    shouldReturnInfinityInTheFirstNumberFormatWhenTheSecondNumberIsInfinity();
    shouldReturnSecondNumberAsNegativeWhenFirstNumberIsInfinityAndSecondNumberIsNegativeAndSameExponentBits();
    shouldReturnInfinityWhenExponentBitsAreNotEqualAndTotalBitsAreLess();
    shouldReturnInfinityWhenExponentBitsAreNotEqualAndTotalBitsAreMore();
    return 0;
}