#include<iostream>
#include "../src/Posit.h"
using namespace std;

#define ASSERT(a,b) if(a != b) throw std::runtime_error("Failed")

Posit* createPosit(uint8_t totalBits,uint8_t exponentBits, uint64_t positValue){
    Posit *num = new Posit(totalBits,exponentBits);
    num ->setPositValue(positValue);
    return num;
}

void shouldReturnZeroForTheNumberZeroAsAPosit(){
    Posit *num = createPosit(8, 0, 0x00);
    ASSERT(num->toFloat(),0);
}
int main(){
    shouldReturnZeroForTheNumberZeroAsAPosit();
    return 0;
}