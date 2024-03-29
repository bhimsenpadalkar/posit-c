#include "Posit.h"
#include <cmath>

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
    uint64_t maskValue = calculatePowerOfTwo(totalBits) - 1;
    this->binaryFormat = posit & maskValue;
}

double Posit::toDouble() {
    return getRepresentedNumber<double, uint64_t>(64, 11, 0x7FF0000000000000);
}

float Posit::toFloat() {
    return getRepresentedNumber<float, uint32_t>(32, 8, 0x7F800000);
}

template<typename T, typename U>
// T is the type either float or double and U is the type either uint32_t or uint64_t
T Posit::getRepresentedNumber(uint8_t totalRepresentationBits, uint8_t exponentBitsForRepresentation,
                              U infiniteValue) const {

    uint64_t positBits = this->binaryFormat << (TOTAL_POSIT_BITS - totalBits);
    bool sign = positBits >> (TOTAL_POSIT_BITS - 1);
    positBits <<= 1;
    positBits = sign ? -positBits : positBits;
    Representation<T, U> inf = Representation<T, U>{};
    inf.binaryValue = infiniteValue;
    if (positBits == 0) {
        return sign ? inf.value : 0;
    }
    const FusedOperationFields &floatFields = extractFields(sign, positBits);
    const long int maxExponentOfFloat = calculatePowerOfTwo(exponentBitsForRepresentation - 1);
    if (floatFields.exponent > maxExponentOfFloat - 1) {
        return sign ? -inf.value : inf.value;
    } else if (floatFields.exponent <= -maxExponentOfFloat) {
        return sign ? -0 : 0;
    }

    uint64_t exponent = floatFields.exponent + maxExponentOfFloat - 1;
    exponent <<= TOTAL_POSIT_BITS - exponentBitsForRepresentation - 1;

    uint64_t floatNumber = 0;
    uint64_t fraction = floatFields.fraction >> (exponentBitsForRepresentation + 1);
    floatNumber = floatNumber | exponent | fraction;

    floatNumber >>= (TOTAL_POSIT_BITS - totalRepresentationBits);
    Representation<T, U> number = Representation<T, U>{};
    number.binaryValue = floatNumber;
    return sign ? -number.value : number.value;

}

FusedOperationFields Posit::extractFields(bool sign, uint64_t positBits) const {
    FusedOperationFields floatFields = FusedOperationFields{false, 0, 0};
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
    while ((usedBits + bitsInExponent) < totalBits && bitsInExponent < exponentBits) {
        exponent *= 2;
        exponent = exponent | (positBits >> (TOTAL_POSIT_BITS - 1));
        positBits <<= 1;
        bitsInExponent++;
    }

    long int finalExponent = calculatePowerOfTwo(this->exponentBits);
    finalExponent *= regime;
    finalExponent += exponent;
    floatFields.sign = sign;
    floatFields.exponent = finalExponent;
    floatFields.fraction = positBits;
    return floatFields;
}

uint64_t Posit::calculatePowerOfTwo(uint8_t power) {
    uint64_t number = 1;
    while (power > 0) {
        number <<= 1;
        power--;
    }
    return number;
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

Posit *Posit::add(Posit *anotherPosit) {
    uint64_t posit1Bits = this->binaryFormat << (TOTAL_POSIT_BITS - totalBits);
    bool sign1 = posit1Bits >> (TOTAL_POSIT_BITS - 1);
    posit1Bits <<= 1;
    posit1Bits = sign1 ? -posit1Bits : posit1Bits;

    uint64_t posit2Bits = anotherPosit->binaryFormat << (TOTAL_POSIT_BITS - anotherPosit->totalBits);
    bool sign2 = posit2Bits >> (TOTAL_POSIT_BITS - 1);
    posit2Bits <<= 1;
    posit2Bits = sign2 ? -posit2Bits : posit2Bits;

    bool isPosit1Zero = sign1 ? false : posit1Bits == 0;
    bool isPosit1Infinite = sign1 ? posit1Bits == 0 : false;
    bool isPosit2Zero = sign2 ? false : posit2Bits == 0;
    bool isPosit2Infinite = sign2 ? posit2Bits == 0 : false;
    if (isPosit1Zero | isPosit2Infinite) {
        return anotherPosit->clone(totalBits, exponentBits);
    }
    if (isPosit2Zero | isPosit1Infinite) {
        return this->clone();
    }
    FusedOperationFields posit1Fields = this->extractFields(sign1, posit1Bits);
    FusedOperationFields posit2Fields = anotherPosit->extractFields(sign2, posit2Bits);
    swapIfExponentIsHigher(posit1Fields, posit2Fields);
    uint64_t exponentDifference = posit1Fields.exponent - posit2Fields.exponent;
    posit2Fields = IncreaseExponent(posit2Fields, exponentDifference);
    if(posit1Fields.sign == posit2Fields.sign){
        return sameSignAddition(posit1Fields, posit2Fields);
    }
    return differentSignAddition(posit1Fields,posit2Fields);
}

FusedOperationFields &Posit::IncreaseExponent(FusedOperationFields &posit2Fields, uint64_t exponentDifference) const {
    for (uint64_t i = 0; i < exponentDifference; i++) {
        posit2Fields.fraction >>= 1;
        posit2Fields.exponent++;
        if (i == 0) {
            uint64_t temp = 1;
            temp <<= 63;
            posit2Fields.fraction = posit2Fields.fraction | temp;
            posit2Fields.hiddenBit = false;
        }
    }
    return posit2Fields;
}

void Posit::swapIfExponentIsHigher(FusedOperationFields &posit1Fields, FusedOperationFields &posit2Fields) const {
    if (posit1Fields.exponent < posit2Fields.exponent) {
        FusedOperationFields temp = posit1Fields;
        posit1Fields = posit2Fields;
        posit2Fields = temp;
    }
}

Posit *Posit::differentSignAddition(FusedOperationFields &posit1Fields, FusedOperationFields &posit2Fields){
    if(posit1Fields.fraction == posit2Fields.fraction && posit2Fields.hiddenBit){
        return new Posit(totalBits,exponentBits);
    }
    leftShiftFractionAndHiddenBit(posit1Fields);
    leftShiftFractionAndHiddenBit(posit2Fields);
    if(posit2Fields.fraction > posit1Fields.fraction){
        FusedOperationFields temp = posit1Fields;
        posit1Fields = posit2Fields;
        posit2Fields = temp;
    }
    posit1Fields.fraction -= posit2Fields.fraction;
    while(!posit1Fields.hiddenBit){
        posit1Fields.hiddenBit = posit1Fields.fraction >> 63;
        posit1Fields.fraction <<= 1;
        posit1Fields.exponent--;
    }
    return create(posit1Fields);
}

void Posit::leftShiftFractionAndHiddenBit(FusedOperationFields &positFields) const {
    uint64_t temp = positFields.hiddenBit;
    temp <<= 63;
    positFields.fraction >>= 1;
    positFields.fraction |= temp;
    positFields.hiddenBit = false;
    positFields.exponent++;
}

Posit *Posit::sameSignAddition(FusedOperationFields &posit1Fields, FusedOperationFields &posit2Fields) {
    uint64_t fraction1 = posit1Fields.fraction;
    uint64_t fraction2 = posit2Fields.fraction;
    fraction1 >>= 1;
    fraction2 >>= 1;
    uint64_t fraction = fraction1 + fraction2;
    uint8_t extra = posit1Fields.hiddenBit + posit2Fields.hiddenBit + (fraction >> 63);
    if (extra > 1) {
        fraction = fraction & 0x7FFFFFFFFFFFFFFF;
        uint64_t temp = extra - 2;
        temp <<= 63;
        fraction = temp | fraction;
        posit1Fields.exponent += 1;
    } else {
        fraction <<= 1;
    }
    posit1Fields.fraction = fraction;
    return create(posit1Fields);
}

Posit *Posit::create(FusedOperationFields floatFields) {
    return create(totalBits,exponentBits,floatFields);
}

Posit *Posit::clone() {
    Posit *newPosit = new Posit(totalBits, exponentBits);
    newPosit->binaryFormat = this->binaryFormat;
    return newPosit;
}

RegimeFields Posit::generateRegime(bool sign, long exponent, uint8_t exponentBits) {
    RegimeFields regimeFields = RegimeFields();
    int base = calculatePowerOfTwo(exponentBits);
    uint64_t regimeBits = 0;
    uint8_t noOfBits = 0;
    uint8_t regime = exponent / base;
    regime = sign ? regime + 1 : regime;
    if (sign) {
        regimeBits = 1;
        noOfBits = regime + 1;
    } else {
        regimeBits = calculatePowerOfTwo(regime + 2) - 2;
        noOfBits = regime + 2;
    }
    regimeFields.noOfBits = noOfBits;
    regimeFields.regime = regimeBits;
    return regimeFields;
}

uint64_t Posit::generateExponent(bool sign, long exponent, uint8_t exponentBits) {
    uint64_t base = calculatePowerOfTwo(exponentBits);
    uint64_t exponentForPosit = exponent % base;
    return sign ? base - exponentForPosit : exponentForPosit;
}

Posit *Posit::clone(uint8_t totalBitsOfPosit, uint8_t exponentBitsOfPosit) {
    if (totalBits == totalBitsOfPosit && exponentBits == exponentBitsOfPosit) {
        return this->clone();
    }

    if(exponentBits == exponentBitsOfPosit){
        Posit* posit = new Posit(totalBitsOfPosit,exponentBitsOfPosit);
        if(totalBitsOfPosit > totalBits){
            posit->binaryFormat = this->binaryFormat << (totalBitsOfPosit - totalBits);
        } else {
            posit->binaryFormat = this->binaryFormat >> (totalBits - totalBitsOfPosit);
        }
        return posit;
    }
    uint64_t positBits = this->binaryFormat << (TOTAL_POSIT_BITS - totalBits);
    bool sign = positBits >> (TOTAL_POSIT_BITS - 1);
    positBits <<= 1;
    positBits = sign ? -positBits : positBits;

    if (positBits == 0x0) {
        Posit *posit = new Posit(totalBitsOfPosit, exponentBitsOfPosit);
        if (!sign) {
            return posit;
        }
        posit->binaryFormat = 1;
        posit->binaryFormat <<= (totalBitsOfPosit - 1);
        return posit;
    }

    FusedOperationFields floatFields = this->extractFields(sign, positBits);

    return create(totalBitsOfPosit, exponentBitsOfPosit, floatFields);
}

Posit *Posit::create(uint8_t totalBits, uint8_t exponentBits, FusedOperationFields floatFields) {
    Posit *positRepresentation = new Posit(totalBits, exponentBits);
    long int exponent = floatFields.exponent;
    bool sign = floatFields.sign;

    if(exponent > ((totalBits - 2) * calculatePowerOfTwo(exponentBits))){
        positRepresentation->setPositValue(calculatePowerOfTwo(totalBits - 1));
        return positRepresentation;
    }

    bool exponentSign = exponent < 0;
    exponent = exponentSign ? -exponent : exponent;

    RegimeFields regimeDetails = generateRegime(exponentSign, exponent, exponentBits);
    uint64_t positExponent = generateExponent(exponentSign, exponent, exponentBits);
    uint64_t positFraction = floatFields.fraction;

    int bitsRequiredForRegime = regimeDetails.noOfBits;
    int bitsRequiredForExponent = 0;
    int bitsRequiredForSign = 1;
    int remainingBits = 0;

    uint64_t positRegime = regimeDetails.regime;
    if (bitsRequiredForRegime > (totalBits - bitsRequiredForSign)) {
        positRegime >>= bitsRequiredForRegime - (totalBits - bitsRequiredForSign);
        bitsRequiredForRegime = totalBits - bitsRequiredForSign;
    }
    remainingBits = totalBits - bitsRequiredForSign - bitsRequiredForRegime;
    positRegime <<= remainingBits;

    if (remainingBits > exponentBits) {
        positExponent <<= remainingBits - exponentBits;
        bitsRequiredForExponent = exponentBits;
    } else if (remainingBits == 0) {
        positExponent = 0;
        bitsRequiredForExponent = 0;
    } else {
        positExponent >>= bitsRequiredForExponent - remainingBits;
        bitsRequiredForExponent = remainingBits;
    }
    remainingBits -= bitsRequiredForExponent;
    positFraction >>= 64 - remainingBits;
    
    uint64_t binary = positRegime | positExponent | positFraction;
    positRepresentation->binaryFormat = binary;

    if(sign){
        positRepresentation->binaryFormat <<= 64 - totalBits;
        positRepresentation->binaryFormat = -positRepresentation->binaryFormat;
        positRepresentation->binaryFormat >>= 64 - totalBits;
    }
    return positRepresentation;
}

Posit *Posit::subtract(Posit *anotherPosit) {
    anotherPosit = anotherPosit->negotiate();  
    return this->add(anotherPosit);
}

Posit *Posit::negotiate() {
    uint64_t positBits = this->binaryFormat << (TOTAL_POSIT_BITS - totalBits);
    bool sign1 = positBits >> (TOTAL_POSIT_BITS - 1);
    positBits <<= 1;
    positBits = sign1 ? -positBits : positBits;
    if(positBits == 0x0){
        return this->clone();
    }
    Posit *newPosit = new Posit(totalBits, exponentBits);
    newPosit->setPositValue(-this->binaryFormat);
    return newPosit;
}
