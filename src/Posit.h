#include <iostream>
struct FusedOperationFields {
    bool sign;
    long int exponent;
    uint64_t fraction;
    bool hiddenBit = true;
};

struct RegimeFields {
    uint64_t regime;
    uint8_t noOfBits;
};

class Posit {

private:
    uint8_t totalBits;
    uint8_t exponentBits;
    uint64_t binaryFormat;

    int convertFloatToPosit(int8_t exponent, uint32_t fraction, bool isNegative) const;

    int calculateRegimeBits(uint64_t remainingBits, bool regimeSign) const;

    template<typename T, typename U>
    T
    getRepresentedNumber(uint8_t totalRepresentationBits, uint8_t exponentBitsForRepresentation, U infiniteValue) const;

    FusedOperationFields extractFields(bool sign, uint64_t positBits) const;

    static uint64_t calculatePowerOfTwo(uint8_t power);
    static Posit* create(uint8_t totalBits, uint8_t exponentBits, FusedOperationFields floatFields);
    Posit* create(FusedOperationFields floatFields);

    Posit *sameSignAddition(FusedOperationFields &posit1Fields, FusedOperationFields &posit2Fields);

    Posit *differentSignAddition(FusedOperationFields &posit1Fields, FusedOperationFields &posit2Fields);

public:
    Posit(uint8_t totalBits, uint8_t exponentBits);

    void setFloatValue(float value);

    void setPositValue(uint64_t posit);

    uint64_t getBinaryFormat();

    double toDouble();

    float toFloat();

    Posit* add(Posit* anotherPosit);

    Posit* clone();

    Posit* clone(uint8_t totalBitsOfPosit,uint8_t exponentBitsOfPosit);

    static RegimeFields generateRegime(bool sign, long exponent,uint8_t exponentBits);

    static uint64_t generateExponent(bool sign, long exponent,uint8_t exponentBits);

    void leftShiftFractionAndHiddenBit(FusedOperationFields &positFields) const;

    void swapIfExponentIsHigher(FusedOperationFields &posit1Fields, FusedOperationFields &posit2Fields) const;

    FusedOperationFields &IncreaseExponent(FusedOperationFields &posit2Fields, uint64_t exponentDifference) const;

    Posit *subtract(Posit *pPosit);
};