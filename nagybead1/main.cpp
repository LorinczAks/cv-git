#include "nMatrix.h"
#include "menu.h"
#include <iostream>
#include <vector>

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main() {
    
    Menu test;
    test.run();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE(constructing matrices) {
    NMatrix a(3);
    NMatrix b(4);

    CHECK(a.getItem(1,2)==0);
    CHECK(b.getItem(3,2)==0);
    CHECK(b.getItem(3,3)==0);
}

TEST_CASE("getItem", "setItem") {
    NMatrix a(3);
    a.setItem(2);
    CHECK(a.getItem(1,3)==2);
    
    a.setItem(3,3, 10);
    CHECK(a.getItem(3,3)==10);

    try {
        a.setItem(1, 2, 111);
    } catch(NMatrix::Exception ex) {
        if(NMatrix::NULLPART) ;
    }
    
    try {
        a.setItem(5, 1, 111);
    } catch(NMatrix::Exception ex) {
        if(NMatrix::OVERINDEXED) ;
    }

    try {
        a.setItem(2, -1, 111);
    } catch(NMatrix::Exception ex) {
        if(NMatrix::OVERINDEXED) ;
    }

    try {
        a.getItem(5, 1);
    } catch(NMatrix::Exception ex) {
        if(NMatrix::OVERINDEXED) ;
    }

    try {
        a.getItem(2, -1);
    } catch(NMatrix::Exception ex) {
        if(NMatrix::OVERINDEXED) ;
    }
}

TEST_CASE("sum") {
    NMatrix a(3);
    NMatrix b(3);
    NMatrix c(2);
    NMatrix result(3);

    a.setItem(3);
    a.setItem(2, 2, 10);

    b.setItem(6);
    b.setItem(1, 3, 1);

    result = a + b;
    CHECK(result.getItem(1,1)==9);
    CHECK(result.getItem(1,3)==4);
    CHECK(result.getItem(2,2)==16);
    try {
        result = a + c;
    } catch(NMatrix::Exception ex) {
        if(NMatrix::NOT_MATCHING_SIZE) ;
    }
}

TEST_CASE("multiply") {
    NMatrix a(5);
    NMatrix b(5);
    NMatrix c(3);
    NMatrix result(5);

    a.setItem(2);
    a.setItem(2, 2, 3);

    b.setItem(5);
    b.setItem(4, 5, 2);

    result = a * b;
    CHECK(result.getItem(1,1)==20);
    CHECK(result.getItem(5,4)==30);
    CHECK(result.getItem(2,2)==15);
    CHECK(result.getItem(4,5)==24);
    try {
        result = a * c;
    } catch(NMatrix::Exception ex) {
        if(NMatrix::NOT_MATCHING_SIZE) ;
    }
}

#endif