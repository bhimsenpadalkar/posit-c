#include <cstdint>
#include "Posit.h"
#include <cmath>
#include <iostream>
#include <type_traits>

using namespace std;

#define IS_NEGATIVE(a) a < 0
const int TOTAL_POSIT_BITS = 64;

template<typename T, typename U>
union Representation {
    T value;
    U binaryValue;
};

Posit::Posit(uint8_t totalBits, uint8_t exponentBits) {
    this->totalBits = totalBits;
    this->exponentBits = exponentBits;
    this->binaryFormat = 0;
}

void Posit::setFloatValue(float value) {
    Representation<float, uint32_t> rep{};
    rep.value = value;
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

void Posit::setPositValue(uint64_t posit) {
    this->binaryFormat = posit;
}

double Posit::toDouble() {
    return getRepresentedNumber<double, uint64_t>(64, 11);
}

float Posit::toFloat() {
    return getRepresentedNumber<float, uint32_t>(32, 8);
}

template<typename T, typename U>
// T is the type either float or double and U is the type either uint32_t or uint64_t
T Posit::getRepresentedNumber(int totalRepresentationBits, int exponentBitsForRepresentation) const {

    uint64_t bitsOnLeftSide = this->binaryFormat << (64 - totalBits);
    U posit = bitsOnLeftSide >> (64 - totalRepresentationBits);
    bool sign = posit >> (totalRepresentationBits - 1);
    posit = sign ? -posit : posit;
    U remainingBits = posit << 1;

    if (remainingBits == 0) {
        Representation<T, U> inf = Representation<T, U>{};
        inf.binaryValue = generateInfiniteValue<U>(totalRepresentationBits, exponentBitsForRepresentation);
        return sign ? inf.value : 0;
    }

    bool regimeSign = remainingBits >> (totalRepresentationBits - 1);
    remainingBits <<= 1;

    int usedBits = 1;
    int regimeBits = 1;
    regimeBits += calculateRegimeBits(remainingBits, totalRepresentationBits, regimeSign);
    remainingBits <<= regimeBits - 1;
    int regime = calculateRegime(regimeSign, regimeBits);

    if (regimeBits != (totalBits - 1) || (regimeBits != totalRepresentationBits - 1)) {
        remainingBits <<= 1;
        regimeBits++;
    }

    usedBits += regimeBits;
    int bitsInExponent = 0;
    U exponent = extractExponent<U>(totalRepresentationBits, usedBits, bitsInExponent, remainingBits);

    int totalExponent = (int) pow(2, exponentBits);
    totalExponent *= regime;
    totalExponent += exponent;
    Representation<T, U> representation = Representation<T, U>{};
    representation.value = (T) pow(2, totalExponent);
    remainingBits >>= exponentBitsForRepresentation + 1;
    representation.binaryValue = representation.binaryValue | remainingBits;
    return sign ? -representation.value : representation.value;
}

template<typename T>
T Posit::extractExponent(int totalRepresentationBits, int usedBits, int bitsInExponent, T &remainingBits) const {
    T exponent = 0;
    while ((usedBits + bitsInExponent) < totalBits && bitsInExponent < exponentBits &&
           (usedBits + bitsInExponent) < totalRepresentationBits) {
        exponent <<= 1;
        exponent = exponent | (remainingBits >> (totalRepresentationBits - 1));
        remainingBits <<= 1;
        bitsInExponent++;
    }
    return exponent;
}

int Posit::calculateRegime(bool regimeSign, int regimeBits) const { return regimeSign ? regimeBits - 1 : -regimeBits; }

template<typename T>
int Posit::calculateRegimeBits(T remainingBits, int totalRepresentationBits, int exponentSign) const {
    int regimeBits = 0;
    while (remainingBits >> (totalRepresentationBits - 1) == exponentSign && regimeBits < (totalBits - 1) &&
           regimeBits < totalRepresentationBits - 1) {
        regimeBits++;
        remainingBits <<= 1;
    }
    return regimeBits;
}

template<typename T>
T Posit::generateInfiniteValue(int totalBits, int exponentBits) const {
    T binaryValue = 0x0;
    T exponent = 0x0;
    int count = 0;
    while (count < totalBits - 1) {
        exponent <<= 1;
        if (count < exponentBits) {
            exponent = exponent | 0x1;
        }
        binaryValue <<= 1;
        binaryValue = binaryValue | 0x1;
        count++;
    }
    binaryValue = binaryValue & exponent;
    return binaryValue;
}

FloatFields Posit::extractFields() {
    FloatFields floatFields = FloatFields{false, 0, 0};
    uint64_t positBits = this->binaryFormat << (TOTAL_POSIT_BITS - totalBits);
    bool sign = positBits >> (TOTAL_POSIT_BITS - 1);
    positBits = sign ? -positBits : positBits;
    positBits <<= 1;

    if(positBits == 0){
        if(sign){
            floatFields.sign = true;
        }
        return floatFields;
    }
    int usedBits = 1;
    bool regimeSign = positBits >> (TOTAL_POSIT_BITS - usedBits);
    positBits <<= 1;
    int regimeBits = 1 + calculateRegimeBits(positBits, regimeSign);
    positBits <<= regimeBits - 1;
    int regime = regimeSign ? regimeBits - 1 : -regimeBits;
    if (regimeBits != (totalBits - 1)) {
        positBits <<= 1;
        regimeBits++;
    }
    usedBits += regimeBits;
    int bitsInExponent = 0;
    long int exponent = 0;
    while((usedBits + bitsInExponent) < totalBits && bitsInExponent < exponentBits){
        exponent *= 2;
        exponent = exponent | (positBits >> (TOTAL_POSIT_BITS - 1));
        positBits <<= 1;
        bitsInExponent++;
    }

    long int finalExponent = getRegimeExponent();
    finalExponent *= regime;
    finalExponent += exponent;
    floatFields.sign = sign;
    floatFields.exponent = finalExponent;
    floatFields.fraction = positBits;
    return floatFields;
}

long int Posit::getRegimeExponent(){
    uint8_t exponentBits = this->exponentBits;
    long int exponent = 1;
    while(exponentBits > 0){
        exponent <<= 1;
        exponentBits--;
    }
    return exponent;
}

int Posit::calculateRegimeBits(uint64_t remainingBits, bool regimeSign) const {
    int regimeBits = 0;
    while (remainingBits >> (TOTAL_POSIT_BITS - 1) == regimeSign &&
           regimeBits <= (totalBits - 2)) { // 2 bits because one is sign bit and one is regime sign bit
        regimeBits++;
        remainingBits <<= 1;
    }
    return regimeBits;
}
