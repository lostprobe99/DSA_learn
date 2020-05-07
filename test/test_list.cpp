#include"../list.hpp"
#include<iostream>
#include<time.h>

using std::cin;
using std::cout;
using std::endl;
void test_list()
{
    cout << "-----list-----" << endl;
    srand(time(NULL));
    list<int> l1;
    for(int i = 0; i < 25; i++)
    {
        if(i == 20)
            continue;
        l1.insert_after(l1.head(), i);
        if(rand() % 2)
            l1.insert_after(l1.head(), i);
    }
    list<int> l2(l1.head()->succ, l1.size());
    list<int> l3(l2, l2.size());
    l1.show();
    cout << "l1.size() = " << l1.size() << endl;;
    l2.show();
    cout << "l2.size() = " << l2.size() << endl;
    l3.show();
    cout << "l3.size() = " << l3.size() << endl;
    l3.deduplicate();
    l3.show();
    cout << "l3.size() = " << l3.size() << endl;

    l3.sort(l3.first(), l3.size());
    l3.show();
    cout << "l3.size() = " << l3.size() << endl;

    posi(int) hit = l3.search(20, l3.size(), l3.tail());
    cout << hit->data << endl;
    cout << hit->succ->data << endl;
    cout << hit->pred->data << endl;
}

int main()
{
    test_list();
    return 0;
}