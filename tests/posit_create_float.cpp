#include<iostream>
#include "../src/Posit.h"
using namespace std;

#define ASSERT(a,b) if(a != b) throw std::runtime_error("Failed")

Posit* createPosit(uint8_t totalBits,uint8_t exponentBits, uint64_t positValue){
    Posit *num = new Posit(totalBits,exponentBits);
    num ->setPositValue(positValue);
    return num;
}

void createFloatValueForPositive(){
    Posit *num = createPosit(8, 0, 0x20);
    ASSERT(num->toFloat(),0.5);
}

void createFloatValueForNegative(){
    Posit *num = createPosit(8, 0, 0xE0);
    ASSERT(num->toFloat(),-0.5);
}

void createDoubleForPositive(){
    uint64_t number = 0;
    number = 0x770E;
    Posit *num = createPosit(16, 1, number);
    ASSERT(num->toFloat(),56.4375);
}
int main(){
    createFloatValueForPositive();
    createFloatValueForNegative();
    createDoubleForPositive();
    return 0;
}