#include"../strmatch.cpp"
#include<iostream>
using std::cout;
using std::endl;

int main()
{
    char * p = "0001";
    char * t = "00000000000001";
    int posi = kmp_match(p, t);
    cout << posi << endl;
    cout << t + posi << endl;


    return 0;
}