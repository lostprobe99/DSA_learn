/*
 * @Author: lostprobe99 
 * @Date: 2020-05-04 16:11:41 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-05 19:36:15
 */
#include<string>
#include<iostream>
#include<fstream>
#include"../bitmap.hpp"
#include"../prime_generator.cpp"
#include"../hashtable.hpp"
using std::cout;
using std::endl;
using std::fstream;
using std::string;

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

void test_hashtable()
{
    Hashtable<string, int> h1;
    cout << h1.size() << endl;
    h1.put("hello", 0);
    h1.put("world", 1);
    cout << h1.size() << endl;
    cout << *(h1.get("hello")) << endl;
    cout << *(h1.get("world")) << endl;
    cout << "h1[\"hello\"] = " << h1["hello"] << endl;
    cout << "change h1[\"hello\"] to 3" << endl;
    h1["hello"] = 3;
    cout << "h1[\"hello\"] = " << h1["hello"] << endl;
}

int main()
{
    // test_bitmap();
    // generate_prime();
    test_hashtable();

    return 0;
}