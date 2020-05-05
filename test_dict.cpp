/*
 * @Author: lostprobe99 
 * @Date: 2020-05-04 16:11:41 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-05 19:36:15
 */
#include<iostream>
#include<fstream>
#include<limits.h>
#include"bitmap.hpp"
#include"pub.cpp"
using std::cout;
using std::endl;
using std::fstream;

void test_bitmap(void)
{
    Bitmap b1;
    b1.set(1);
    b1.set(2);
    b1.set(3);
    b1.dump("bitmap.txt");
    char *s = b1.bits2string(8);
    cout << s << endl;
    delete [] s;

    Bitmap b2("bitmap.txt");
    s = b2.bits2string(8);
    cout << s << endl;
    delete [] s;
}

void generate_prime()
{
    const int prime_limit = 1048576;
    const char *filename = "prime-1048576-bitmap.out";
    eratosthenes(prime_limit, filename);
}

int main()
{
    // test_bitmap();
    generate_prime();

    return 0;
}