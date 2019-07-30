#include <cstdint>
#include "Posit.h"
#include <math.h>
#include <iostream>

using namespace std;

#define IS_NEGATIVE(a) a < 0

union FloatRep {
    float floatValue;
    uint32_t binaryValue;
};

union DoubleRep {
    double doubleValue;
    uint64_t binaryValue;
};

Posit::Posit(uint8_t totalBits, uint8_t exponentBits) {
    this->totalBits = totalBits;
    this->exponentBits = exponentBits;
}

void Posit::setFloatValue(float value) {
    FloatRep rep{};
    rep.floatValue = value;

    int floatExponentBits = 8;
    int floatSignBits = 1;
    int totalFloatBits = 32;
    int8_t exponent = (rep.binaryValue >> (totalFloatBits - (floatExponentBits + floatSignBits)) & 0x00FF) - 127;
    uint32_t fraction = (rep.binaryValue & 0x3FFFFF);

    this->binaryFormat = convertFloatToPosit(exponent, fraction, IS_NEGATIVE(value));
}

int Posit::convertFloatToPosit(int8_t exponent, uint32_t fraction, bool isNegative) const {
    int maxFractionBits = 23;
    int base = (int) pow(2, exponentBits);

    int regime = exponent / base;
    regime = IS_NEGATIVE(regime) ? (regime - 1) : regime;

    int positExponent = exponent % base;
    positExponent = IS_NEGATIVE(positExponent) ? (base + positExponent) : positExponent;

    uint32_t positFraction = fraction;

    uint32_t positRegime = 0;
    int bitsRequiredForRegime = 0;
    int bitsRequiredForExponent = 0;
    int bitsRequiredForSign = 1;

    if (IS_NEGATIVE(exponent)) {
        positRegime = 1;
        bitsRequiredForRegime = 1 - regime;
    } else {
        positRegime = (int) (pow(2, (regime + 2))) - 2;
        bitsRequiredForRegime = regime + 2;
    }

    int remainingBits = totalBits - (bitsRequiredForRegime + bitsRequiredForSign);

    if (bitsRequiredForRegime > (totalBits - bitsRequiredForSign)) {
        positRegime >>= bitsRequiredForRegime - (totalBits - bitsRequiredForSign);
        remainingBits = 0;
        bitsRequiredForRegime = totalBits - bitsRequiredForSign;
    }

    if (remainingBits > exponentBits) {
        bitsRequiredForExponent = exponentBits;
    } else if (remainingBits == 0) {
        positExponent = 0;
        bitsRequiredForExponent = 0;
    } else {
        bitsRequiredForExponent = remainingBits;
    }
    positExponent >>= exponentBits - bitsRequiredForExponent;

    remainingBits -= bitsRequiredForExponent;

    positRegime <<= totalBits - (bitsRequiredForSign + bitsRequiredForRegime);
    positExponent <<= remainingBits;
    positFraction >>= maxFractionBits - remainingBits;
    int finalPosit = positRegime | positExponent | positFraction;

    if (isNegative) {
        finalPosit = -finalPosit;
    }
    return finalPosit;
}

uint64_t Posit::getBinaryFormat() {
    return binaryFormat;
}

double Posit::toDouble() {
    int positBits = 64;
    uint64_t posit = this->binaryFormat << (positBits - totalBits);
    bool sign = posit >> (positBits - 1);
    posit = sign ? -posit : posit;
    uint64_t remainingBits = posit << 1;

    if(remainingBits == 0){
        DoubleRep inf = DoubleRep{};
        inf.binaryValue = 0x7FF0000000000000;
        return sign ?  inf.doubleValue : 0;
    }

    bool exponentSign = remainingBits >> (positBits - 1);
    remainingBits <<= 1;

    int usedBits = 1;
    int regimeBits = 1;

    while (remainingBits >> (positBits - 1) == exponentSign && regimeBits < (totalBits - 1)) {
        regimeBits++;
        remainingBits <<= 1;
    }

    int regime = exponentSign ? regimeBits - 1 : -regimeBits;

    if (regimeBits != (totalBits - 1)) {
        remainingBits <<= 1;
        regimeBits++;
    }

    usedBits += regimeBits;
    int bitsInExponent = 0;
    uint64_t exponent = 0;
    while ((usedBits + bitsInExponent) < totalBits && bitsInExponent < exponentBits) {
        exponent <<= 1;
        exponent = exponent | (remainingBits >> (positBits - 1));
        remainingBits <<= 1;
        bitsInExponent++;
    }

    int doubleExponent = (int) pow(2, exponentBits);
    doubleExponent = (doubleExponent * regime);
    doubleExponent += exponent;

    DoubleRep doubleValue = DoubleRep{};
    doubleValue.doubleValue = pow(2, doubleExponent);
    remainingBits >>= 12;
    doubleValue.binaryValue = doubleValue.binaryValue | remainingBits;
    cout << -doubleValue.doubleValue << endl;
    cout << sign << endl;
    return sign ? -doubleValue.doubleValue : doubleValue.doubleValue;
}

void Posit::setPositValue(uint64_t posit) {
    this->binaryFormat = posit;
}

float Posit::toFloat() {
    return 0;
}
