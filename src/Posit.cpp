#include <cstdint>

using namespace std;

class Posit {

private:
    uint8_t totalBits;
    uint8_t exponentBits;

    Posit(uint8_t totalBits, uint8_t exponentBits) {
        this->totalBits = totalBits;
        this->exponentBits = exponentBits;
    }

};