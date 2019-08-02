#include "../src/Posit.h"
#include "Utils.h"

using namespace std;

void verifyAdditionOfPosits(Posit* posit1,Posit* posit2,Posit* expectedPosit){
    Posit *actualPosit = posit1->add(posit2);
    Utils::verifyPosits(expectedPosit, actualPosit);
}

void shouldReturnZeroPositWhenTwoPositsAreAdded() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x0);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x0);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
};

void shouldReturnAnotherPositValueWhenTheCurrentPositIsZero() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x40);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
};

void shouldReturnCurrentPositValueWhenTheAnotherPositValueIsZero() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x40);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x0);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
};

void shouldReturnInfinityWhenTheCurrentValueIsInfinity(){
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x80);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x01);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x80);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
}

void shouldReturnInfinityWhenTheAnotherPositValueIsInfinity(){
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x10);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x80);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x80);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
}

void shouldReturnAddedValueWhenBothExponentsAndSignsAreEqual(){
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x6C);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x62);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x73);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
}

void shouldReturnAddedValueWhenBothExponentAndSignsAreEqual1(){
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x6D);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x6A);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x75);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
}

int main() {
    shouldReturnZeroPositWhenTwoPositsAreAdded();
    shouldReturnAnotherPositValueWhenTheCurrentPositIsZero();
    shouldReturnCurrentPositValueWhenTheAnotherPositValueIsZero();
    shouldReturnInfinityWhenTheCurrentValueIsInfinity();
    shouldReturnInfinityWhenTheAnotherPositValueIsInfinity();
    shouldReturnAddedValueWhenBothExponentsAndSignsAreEqual();
    shouldReturnAddedValueWhenBothExponentAndSignsAreEqual1();
    return 0;
};