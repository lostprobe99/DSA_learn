#include<iostream>
using std::cout;
using std::endl;

#ifndef COUNT
#define COUNT
#endif

#include"../strmatch.cpp"

void f(void)
{
    int n, m;
    std::cin >> n;
    for(int i = 0; i < n; i++)
    {
        std::cin >> m;
        int sum = 1, pre = 1;
        for(int j = 2; j <= m; j++)
        {
            pre += j;
            sum += pre;
        }
        cout << sum << endl;
    }
}

int main()
{
    f();
    return 0;
    char * p = "0000";
    char * t = "00010001000100010000";
    int posi = kmp_match(p, t);
    cout << "offset of string is:\n" << posi << endl;
    cout << t + posi << endl;

    #if 0
    // BC算法 最好情况
    p = "0000";
    t = "00010001000100010000";
    #endif

    posi = bm_match(p, t);
    cout << "offset of string is:\n" << posi << endl;
    cout << t + posi << endl;

    posi = kr_match(p, t);
    cout << "offset of string is:\n" << posi << endl;
    cout << t + posi << endl;

    return 0;
}