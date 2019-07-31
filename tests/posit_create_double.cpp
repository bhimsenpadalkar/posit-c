#include<iostream>
#include <limits>
#include "../src/Posit.h"
using namespace std;

#define ASSERT(a,b) if(a != b) throw std::runtime_error("Failed")

Posit* createPosit(uint8_t totalBits,uint8_t exponentBits, uint64_t positValue){
    Posit *num = new Posit(totalBits,exponentBits);
    num ->setPositValue(positValue);
    return num;
}

void shouldConvertPositValueIntoFloatForSmallPositivePositWhenNoExponentBits(){
    Posit *num = createPosit(8, 0, 0x20);
    ASSERT(num->toDouble(), 0.5);
}

void shouldConvertPositValueIntoFloatForSmallNegativePositWhenNoExponentBits(){
    Posit *num = createPosit(8, 0, 0xE0);
    ASSERT(num->toDouble(), -0.5);
}

void shouldConvertPositivePositValueIntoDouble(){
    Posit *num = createPosit(16, 1, 0x770E);
    ASSERT(num->toDouble(), 56.4375);
}

void shouldConvertNegativePositValueIntoDouble(){
    Posit *num = createPosit(16, 1, 0xAA00);
    ASSERT(num->toDouble(), -2.75);
}

void shouldGiveZeroRepresentationOfPositToDouble(){
    Posit *num = createPosit(8,0,0x00);
    ASSERT(num->toDouble(),0);
}

void shouldGiveInfiniteRepresentationOfPositToDouble(){
    Posit *num = createPosit(8,0,0x80);

    union DoubleRep {
        double doubleValue;
        uint64_t binaryValue;
    };
    DoubleRep inf = DoubleRep{};
    inf.doubleValue = num->toDouble();
    ASSERT(inf.binaryValue,0x7FF0000000000000);
}

int main(){
    shouldConvertPositValueIntoFloatForSmallPositivePositWhenNoExponentBits();
    shouldConvertPositValueIntoFloatForSmallNegativePositWhenNoExponentBits();
    shouldConvertPositivePositValueIntoDouble();
    shouldConvertNegativePositValueIntoDouble();
    shouldGiveZeroRepresentationOfPositToDouble();
    shouldGiveInfiniteRepresentationOfPositToDouble();
    return 0;
}