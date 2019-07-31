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

    template<typename T>
    int calculateRegimeBits(T remainingBits, int totalRepresentationBits, int exponentSign) const;

    int calculateRegimeBits(uint64_t remainingBits, bool regimeSign) const;

    template<typename T, typename U>
    T getRepresentedNumber(int totalRepresentationBits, int exponentBitsForRepresentation) const;

    template<typename T>
    T generateInfiniteValue(int totalBits, int exponentBits) const;

    template<typename T>
    T extractExponent(int totalRepresentationBits, int usedBits, int bitsInExponent, T &remainingBits) const;

public:
    Posit(uint8_t totalBits, uint8_t exponentBits);

    void setFloatValue(float value);

    void setPositValue(uint64_t posit);

    uint64_t getBinaryFormat();

    double toDouble();

    float toFloat();

    int calculateRegime(bool regimeSign, int regimeBits) const;

    FloatFields extractFields();
};