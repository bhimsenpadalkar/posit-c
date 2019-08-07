#include "Posit.h"
#include "Utils.h"
#include "gtest/gtest.h"

using namespace std;

void verifySubtractionOfPosits(Posit *posit1, Posit *posit2, Posit *expectedPosit) {
    Posit *actualPosit = posit1->subtract(posit2);
    Utils::verifyPosits(expectedPosit, actualPosit);
}


TEST(Posit_subtract, shouldReturnZeroPositWhenTwoPositsAreAdded) {
    Posit *posit1 = Utils::createPositByUint(8, 0, 0x0);
    Posit *posit2 = Utils::createPositByUint(8, 0, 0x0);

    Posit *expectedPosit = Utils::createPositByUint(8, 0, 0x0);
    verifySubtractionOfPosits(posit1, posit2, expectedPosit);
}