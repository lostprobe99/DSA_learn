#include"../pq_ComplHeap.hpp"
#include"pub_print.h"
#include"../leftheap.hpp"
#include<iostream>
#include<ctime>
using std::cout;
using std::endl;

print<int> p;

void test_ComplHeap(void)
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

void test_leftheap(void)
{
    leftheap<int> lh1;
    const int max_limit = 1e4;
    srand(time(NULL));
    cout << "follow is insert random number and print max" << endl;
    for(int i = 0; i < 10; i++)
    {
        lh1.insert(rand() % max_limit);
        cout << lh1.get_max() << endl;
    }
    cout << "follow is level trav" << endl;
    lh1.trav_level(lh1.root(), p);
}

int main()
{
    // test_ComplHeap();
    test_leftheap();

    return 0;
}