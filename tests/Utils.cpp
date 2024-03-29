//
// Created by sai-ganesh on 31/07/19.
//

#include "Utils.h"
#include "Posit.h"
#include "gtest/gtest.h"

Posit *Utils::createPositByUint(uint8_t totalBits, uint8_t exponentBits, uint64_t positValue) {
    Posit *num = new Posit(totalBits, exponentBits);
    num->setPositValue(positValue);
    return num;
}

Posit *Utils::createPositByFloat(uint8_t totalBits, uint8_t exponentBits, float floatValue) {
    Posit *num = new Posit(totalBits, exponentBits);
    num->setFloatValue(floatValue);
    return num;
}

void Utils::verifyPosits(Posit *posit1, Posit *posit2) {
    ASSERT_EQ(posit1->getBinaryFormat(), posit2->getBinaryFormat());
}
