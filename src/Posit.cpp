#include <cstdint>
#include "Posit.h"
#include <math.h>
#include <iostream>

using namespace std;

#define IS_NEGATIVE(a) a<0

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
    int floatExponentBits = 8;
    int floatSignBits = 1;
    int totalFloatBits = 32;
    int8_t exponent = ((rep.binaryValue >> (totalFloatBits - (floatExponentBits + floatSignBits))) & 0x00FF) - 127;
    uint32_t fraction = (rep.binaryValue & 0x3FFFFF);

    this->binaryFormat = convertFloatToPosit(exponent, fraction, IS_NEGATIVE(value));
    cout << this->binaryFormat <<  "\n \n"<< endl;
}

int Posit::convertFloatToPosit(int8_t exponent, uint32_t fraction, bool isNegative) const {
    int maxFractionBits = 23;
    int base = (int) pow(2, exponentBits);
    int regime = exponent / base;
    regime = IS_NEGATIVE(regime) ? (regime - 1) : regime;
    int positExponent = exponent % base;
    positExponent = IS_NEGATIVE(positExponent) ? (base + positExponent) : positExponent;
    uint32_t positRegime = 0;
    int bitsRequiredForRegime = 0;
    int bitsRequiredForSign = 1;

    if (IS_NEGATIVE(exponent)) {
        positRegime = 1;
        bitsRequiredForRegime = 1 - regime;
    } else {
        positRegime = (int) (pow(2, (regime + 2))) - 2;
        bitsRequiredForRegime = regime + 2;
    }

    int usedBits = bitsRequiredForRegime + bitsRequiredForSign;
    int remainingBits = totalBits - usedBits;
    int bitsRequiredForExponent = exponentBits;
    if (remainingBits < exponentBits) {
        bitsRequiredForExponent = remainingBits;
    }

    if(remainingBits <= 0){
        positExponent = 0;
        bitsRequiredForExponent = 0;
    }

    remainingBits -= bitsRequiredForExponent;

    uint32_t positFraction = fraction >> (maxFractionBits - remainingBits);

    cout << "bitsRequiredForRegime: " << bitsRequiredForRegime << endl;
    cout << "remainingBits: " << remainingBits << endl;

    if(remainingBits < 0){
        cout << "positRegime: " << positRegime << endl;
        positExponent >>= -remainingBits;
        positRegime >>= -remainingBits;
        positFraction >>= -remainingBits;
        bitsRequiredForRegime-= -remainingBits;
        bitsRequiredForExponent-= remainingBits + 1;
        cout << "bitsRequiredForRegime: " << bitsRequiredForRegime << "\n" << endl;
    }

    cout << "bitsRequiredForRegime: " << bitsRequiredForRegime << endl;
    cout << "bitsRequiredForExponent: " << bitsRequiredForExponent << endl;
    cout << "regimeShift: " << totalBits - (bitsRequiredForSign + bitsRequiredForRegime) << endl;
    cout << "remainingBits: " << remainingBits << endl;
    cout << "positRegime: " << positRegime << endl;
    positRegime <<= totalBits - (bitsRequiredForSign + bitsRequiredForRegime);
    cout << "positRegime: " << positRegime << endl;
    positExponent <<= totalBits - (bitsRequiredForSign + bitsRequiredForRegime + bitsRequiredForExponent);
    positExponent >>= exponentBits - bitsRequiredForExponent;
    cout << "positExponent: " << positExponent << endl;
    int finalPosit = positRegime | positExponent | positFraction;

    if (isNegative) {
        finalPosit = -finalPosit;
    }
    return finalPosit;
}

uint64_t Posit::getBinaryFormat() {
    return binaryFormat;
}
