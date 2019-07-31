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

void shouldReturnTheFloatFieldsOfPositRepresentationForNegativeTwo(){
    Posit *num = Utils::createPositByUint(8,2,0xB8);
    FloatFields expectedFields = FloatFields{true, 1, 0x0};
    FloatFields actualFields = num->extractFields();
    verifyFloatFields(expectedFields, actualFields);
}

void shouldReturnTheFloatFieldsOfPositRepresentationForTwoWhenRegimeBitsAreThere(){
    Posit *num = Utils::createPositByUint(8,2,0x60);
    FloatFields expectedFields = FloatFields{false, 4, 0x0};
    FloatFields actualFields = num->extractFields();
    verifyFloatFields(expectedFields, actualFields);
}

void shouldReturnTheFloatFieldsOfPositRepresentationForTwoWhenRegimeBitsAreThereAndExponentHaveSomeValue(){
    Posit *num = Utils::createPositByUint(8,2,0x64);
    FloatFields expectedFields = FloatFields{false, 5, 0x0};
    FloatFields actualFields = num->extractFields();
    verifyFloatFields(expectedFields, actualFields);
}


void shouldReturnTheFloatFieldsOfPositRepresentationForThree(){
    Posit *num = Utils::createPositByUint(8,2,0x66);
    uint64_t fraction = 1;
    fraction <<= 63;
    FloatFields expectedFields = FloatFields{false, 5, fraction };
    FloatFields actualFields = num->extractFields();
    verifyFloatFields(expectedFields, actualFields);
}

int main(){
    shouldReturnTheFloatFieldsOfPositRepresentationForZero();
    shouldReturnTheFloatFieldsOfPositRepresentationForInfinity();
    shouldReturnTheFloatFieldsOfPositRepresentationForTwo();
    shouldReturnTheFloatFieldsOfPositRepresentationForNegativeTwo();
    shouldReturnTheFloatFieldsOfPositRepresentationForTwoWhenRegimeBitsAreThere();
    shouldReturnTheFloatFieldsOfPositRepresentationForTwoWhenRegimeBitsAreThereAndExponentHaveSomeValue();
    shouldReturnTheFloatFieldsOfPositRepresentationForThree();
    return 0;
}