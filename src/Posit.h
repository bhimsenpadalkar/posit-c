class Posit {

private:
    uint8_t totalBits;
    uint8_t exponentBits;
    float floatValue;
    uint64_t binaryFormat;
    int convertFloatToPosit(int8_t exponent, uint32_t fraction, bool isNegative) const;

public:
    Posit(uint8_t totalBits, uint8_t exponentBits);
    void setFloatValue(float value);
    uint64_t getBinaryFormat();
};