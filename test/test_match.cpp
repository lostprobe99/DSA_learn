#include<iostream>
using std::cout;
using std::endl;

#ifndef COUNT
#define COUNT
#endif

#define V1
#undef V1

#include"../strmatch.cpp"

int main()
{
    char * p = "0000";
    char * t = "00010001000100010000";
    int posi = kmp_match(p, t);
    cout << "offset of string is:\n" << posi << endl;
    cout << t + posi << endl;

    #if 1
    // BC算法 最好情况
    p = "0000";
    t = "00010001000100010000";
    #endif
    // p = "1000";
    // t = "00000000000000001000";

    posi = bm_match(p, t);
    cout << "offset of string is:\n" << posi << endl;
    cout << t + posi << endl;

    return 0;
}