#include"bitmap.hpp"
#include<algorithm>
#include<iostream>
void eratosthenes(int n, const char * const file)
{
    Bitmap b(n);
    b.set(0), b.set(1); // 0 和 1 不是素数
    for(int i = 2; i < n; i++)
    {
        if(!b.test(i))  // !test 代表是素数
            for(int j = std::min(i, 46340) * std::min(i, 46340); j < n; j += i)
                b.set(j);
    }
    b.dump(file);
}