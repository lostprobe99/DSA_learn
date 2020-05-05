/*
 * @Author: lostprobe99 
 * @Date: 2020-05-04 16:11:41 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-05 15:28:13
 */
#include<iostream>
#include"bitmap.hpp"
using std::cout;
using std::endl;

size_t hash_code(char s[])
{
    int h = 0;
    for(; *s != '\0'; s++)
    {
        h = (h << 5) | (h >> 27);
        h += (int)(*s);
    }
    return (size_t)h;
}

void test_hashcode(void)
{
    cout << hash_code("Hello, World") << endl;
    cout << hash_code("hello, world") << endl;
    cout << hash_code("Hello, World\n") << endl;
    cout << hash_code("hello, world\n") << endl;
    cout << hash_code("a") << endl;
    cout << hash_code("b") << endl;
    cout << hash_code("tommarvoloriddle") << endl;
    cout << hash_code("iamlordvoldemort") << endl;
    cout << hash_code("文件") << endl;
    cout << sizeof(char) << endl;
}

void test_bitmap(void)
{
    Btimap b1;
    b1.set(1);
    b1.set(2);
    b1.set(3);
    b1.dump("bitmap.txt");
    char *s = b1.bits2string(8);
    cout << s << endl;
    delete [] s;

    Btimap b2("bitmap.txt");
    s = b2.bits2string(8);
    cout << s << endl;
    delete [] s;
}

int main()
{
    test_bitmap();

    return 0;
}