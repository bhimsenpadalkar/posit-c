#include <iostream>
struct FloatFields {
    bool sign;
    long int exponent;
    uint64_t fraction;
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

    FloatFields extractFields(bool sign, uint64_t positBits) const;

    static long int calculatePowerOfTwo(uint8_t power);

    bool isZero();

    bool isInfinite();

public:
    Posit(uint8_t totalBits, uint8_t exponentBits);

    void setFloatValue(float value);

    void setPositValue(uint64_t posit);

    uint64_t getBinaryFormat();

    double toDouble();

    float toFloat();

    Posit* add(Posit* anotherPosit);

    Posit* clone();
};