#include <iostream>
#include"btree.h"
#include"btree.hpp"

using std::endl;
using std::cin;
using std::cout;

template <typename T>
class print
{
public:
    print(){}
    void operator()(const T& e)
    {   cout << e << endl;    }
};

template <typename T>
void insert(btree<T>& t)
{
    t.insertAsRoot(0);
    t.insertAsLc(t.root(), 1);
    t.insertAsRc(t.root(), 2);
    t.insertAsLc(t.root()->lchild, 3);
    t.insertAsLc(t.root()->rchild, 4);
    t.insertAsRc(t.root()->rchild, 5);
}

template <typename T, typename VST>
void trav(btree<T>& t, VST& visit)
{
    cout << endl;
    t.trav_pre(t.root(), visit);
    cout << endl;
    t.trav_pre_loop_I(t.root(), visit);
    cout << endl;
    t.trav_pre_loop_II(t.root(), visit);
    cout << endl;

    t.trav_in(t.root(), visit);
    cout << endl;
    t.trav_in_loop_I(t.root(), visit);
    cout << endl;

    t.trav_level(t.root(), visit);
    cout << endl;
    t.trav_level_stack(t.root(), visit);
    cout << endl;
}

int main()
{
    btree<int> tree1;
    print<int> p;

    insert(tree1);
    trav(tree1, p);

    return 0;
}

