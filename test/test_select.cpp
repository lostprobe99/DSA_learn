/*
 * @Author: lostprobe99 
 * @Date: 2020-05-12 12:13:55 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-12 12:22:13
 */
#include"../vec.hpp"
#include"../select.cpp"
#include"pub_print.h"

int main()
{
    int nums[] = {716,26,316,193,315,535,803,826,99,885};
    vec<int> v1(nums, 0, 10);
    // int maj;
    // if(majority(v1, maj))
    //     cout << maj << endl;
    cout << v1[2] << endl;
    quick_select(v1, 2);
    cout << v1[2] << endl;
    print<int> p;
    v1.traverse(p);

    return 0;
}