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

void shouldReturnTheFloatFieldsOfPositRepresentationForInfinity(){
    Posit *num = Utils::createPositByUint(8, 0, 0x80);
    FloatFields expectedFields = FloatFields{true, 0, 0};
    FloatFields actualFields = num->extractFields();
    verifyFloatFields(expectedFields, actualFields);
}


void shouldReturnTheFloatFieldsOfPositRepresentationForTwo(){
    Posit *num = Utils::createPositByUint(8,2,0x48);
    FloatFields expectedFields = FloatFields{false, 1, 0x0};
    FloatFields actualFields = num->extractFields();
    verifyFloatFields(expectedFields, actualFields);
}

int main(){
    shouldReturnTheFloatFieldsOfPositRepresentationForZero();
    shouldReturnTheFloatFieldsOfPositRepresentationForInfinity();
    shouldReturnTheFloatFieldsOfPositRepresentationForTwo();
    return 0;
}