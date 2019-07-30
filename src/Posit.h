class Posit {

private:
    uint8_t totalBits;
    uint8_t exponentBits;
    uint64_t binaryFormat;
    int convertFloatToPosit(int8_t exponent, uint32_t fraction, bool isNegative) const;
    double getDouble(bool sign, uint64_t remainingBits, int doubleExponent, int exponentBitsForRepresentation) const;

public:
    Posit(uint8_t totalBits, uint8_t exponentBits);
    void setFloatValue(float value);
    void setPositValue(uint64_t posit);
    uint64_t getBinaryFormat();
    double toDouble();
    float toFloat();

    float getDouble1(bool sign, uint32_t remainingBits, int floatExponent, int exponentBitsForRepresentation) const;

    template<typename T, typename U>
    T getRepresentedNumber(bool sign, U remainingBits, int exponent, int exponentBitsForRepresentation);
};