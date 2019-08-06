//
// Created by sai-ganesh on 06/08/19.
//
#include "PositAddTest.h"
#include "PositCreateTest.h"
#include "iostream"
#include "PositCreateDoubleTest.h"
#include "PositCreateFloatTest.h"

using namespace std;
int main(){
    Testable *pAdd = new PositAddTest();
    pAdd->test();

    Testable *pCreate = new PositCreateTest();
    pCreate->test();

    Testable *pCreateDouble = new PositCreateDoubleTest();
    pCreateDouble->test();

    Testable *pCreateFloat = new PositCreateFloatTest();
    pCreateFloat->test();
}
