#pragma once

#include"vec.hpp"
#include"vec.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

void test_vec();

class print{
public:
    print(){}
    void operator()(int & e)
    {   printf("%d ", e);   }
};
class sum{
public:
    int _sum;
    sum() : _sum(0) {}
    void operator()(int & e)
    {   _sum += e;   }
};

