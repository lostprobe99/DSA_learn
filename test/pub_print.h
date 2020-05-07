#include<iostream>
using std::cout;
using std::endl;
template <typename T>
class print
{
public:
    print(){}
    void operator()(const T& e)
    {   cout << e << endl;    }
};