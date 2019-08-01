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

void shouldReturnTheNonZeroValueOfPositWhenBothTotalBitsAndExponentsAreEqualAreAdded() {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x40);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
};

void shouldReturnTheNonZeroValueOfPositWhenBothTotalBitsAreEqualAndExponentsSizesAreNotEqualAreAdded(){
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 1, 0x40);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x40);
    verifyAdditionOfPosits(posit1,posit2,expectedPosit);
}

int main() {
    shouldReturnZeroPositWhenTwoPositsAreAdded();
    shouldReturnTheNonZeroValueOfPositWhenBothTotalBitsAndExponentsAreEqualAreAdded();
    shouldReturnTheNonZeroValueOfPositWhenBothTotalBitsAreEqualAndExponentsSizesAreNotEqualAreAdded();
    return 0;
};