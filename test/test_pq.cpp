#include"../pq_ComplHeap.hpp"
#include"pub_print.h"
#include<iostream>
using std::cout;
using std::endl;

print<int> p;

void test_pq(void)
{
    pq_ComplHeap<int> pq1;
    pq1.insert(1);
    cout << pq1.get_max() << endl;
    pq1.insert(5);
    cout << pq1.get_max() << endl;
    pq1.insert(5);
    cout << pq1.get_max() << endl;
    pq1.traverse(p);
    pq1.del_max();
    cout << "deleted max" << endl;
    pq1.traverse(p);
    pq1.del_max();
    cout << "deleted max" << endl;
    pq1.traverse(p);

    cout << "pq2" << endl;
    int nums[] = {19, 117, 124, 124, 308, 539, 773, 819, 847, 936};
    pq_ComplHeap<int> pq2(nums, 10);
    pq2.traverse(p);
}

int main()
{
    test_pq();

    return 0;
}