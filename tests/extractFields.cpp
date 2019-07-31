#include<iostream>
#include <cstdint>
#include "../src/Posit.h"
#include "Utils.h"
using namespace std;

void verifyFloatFields(const FloatFields &expectedFields, const FloatFields &actualFields) {
    ASSERT(expectedFields.sign, actualFields.sign);
    ASSERT(expectedFields.exponent, actualFields.exponent);
    ASSERT(expectedFields.fraction, actualFields.fraction);
}

void shouldReturnTheFloatFieldsOfPositRepresentationForZero(){
    Posit *num = Utils::createPositByUint(8, 0, 0x00);
    FloatFields expectedFields = FloatFields{false, 0, 0};
    FloatFields actualFields = num->extractFields();
    verifyFloatFields(expectedFields, actualFields);
}

int main(){
    shouldReturnTheFloatFieldsOfPositRepresentationForZero();
    return 0;
}