#include <cstdint>
#include "Posit.h"
#include <math.h>

using namespace std;

union FloatRep {
    float floatValue;
    uint32_t binaryValue;
};

Posit::Posit(uint8_t totalBits, uint8_t exponentBits) {
    this->totalBits = totalBits;
    this->exponentBits = exponentBits;
}

void Posit::setFloatValue(float value) {
    FloatRep rep{};
    rep.floatValue = value;

    this->floatValue = value;
    int maxFractionBits = 23;
    int8_t exponent = ((rep.binaryValue >> maxFractionBits) & 0x00FF) - 127;
    uint32_t fraction = (rep.binaryValue & 0x3FFFFF);

    int base = (int) pow(2, this->exponentBits);
    int regime = exponent / base;
    regime = regime < 0 ? (regime - 1) : regime;
    int positExponent = exponent % base;
    positExponent = positExponent < 0 ? (base + positExponent) : positExponent;
    uint32_t positRegime;
    int bitsRequiredForRegime;

    if (exponent >= 0) {
        positRegime = (int) (pow(2, (regime + 2))) - 2;
        bitsRequiredForRegime = regime + 2;
    } else {
        positRegime = 1;
        bitsRequiredForRegime = 1 - regime;
    }

    int usedBits = bitsRequiredForRegime + 1;
    int remainingBits = this->totalBits - usedBits;
    int bitsRequiredForExponent = this->exponentBits;
    if(remainingBits < this->exponentBits) {
        bitsRequiredForExponent = remainingBits;
    }

    remainingBits -= bitsRequiredForExponent;

    uint32_t positFraction = fraction >> (maxFractionBits-remainingBits);

    int bitsRequiredForSign = 1;
    positRegime <<= this->totalBits - (bitsRequiredForSign + bitsRequiredForRegime);
    positExponent <<= this->totalBits - (bitsRequiredForSign + bitsRequiredForRegime + bitsRequiredForExponent);

    int finalPosit = positRegime | positExponent | positFraction;

    this->binaryFormat = finalPosit;
}

uint64_t Posit::getBinaryFormat() {
    return binaryFormat;
}
