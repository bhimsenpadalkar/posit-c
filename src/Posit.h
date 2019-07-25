class Posit {

private:
    uint8_t totalBits;
    uint8_t exponentBits;
    float floatValue;
    uint64_t binaryFormat;

public:
    Posit(uint8_t totalBits, uint8_t exponentBits);
    void setFloatValue(float value);
    uint64_t getBinaryFormat();

};