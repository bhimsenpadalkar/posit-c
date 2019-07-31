//
// Created by sai-ganesh on 31/07/19.
//

#include "Utils.h"
#include "../src/Posit.h"

Posit* Utils::createPositByUint(uint8_t totalBits, uint8_t exponentBits, uint64_t positValue) {
    Posit *num = new Posit(totalBits, exponentBits);
    num->setPositValue(positValue);
    return num;
}

Posit *Utils::createPositByFloat(uint8_t totalBits, uint8_t exponentBits, float floatValue) {
    Posit *num = new Posit(totalBits, exponentBits);
    num->setFloatValue(floatValue);
    return num;
}