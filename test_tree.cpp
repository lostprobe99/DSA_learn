#include <iostream>
#include"btree.hpp"
#include"bst.hpp"
#include"avl.hpp"

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
}

template<typename T>
void isnert_bst(BST<T>& b1)
{
    // cout << b1.insert(42)->data << endl;
    bnodePosi(int) t1 = b1.insert(42);
    bnodePosi(int) t2 = b1.insert(8);
    // exit(0);
    // b1.insert(64);
    // b1.insert(40);
}

template<typename T, typename VST>
void trav_bst(BST<T>& b1, VST& visit)
{
    // cout << "pre tarv" << endl;
    // b1.trav_pre(b1.root(), visit);
    // cout << endl;

    cout << "in tarv" << endl;
    b1.trav_in(b1.root(), visit);
    cout << endl;

    // cout << "level tarv" << endl;
    // b1.trav_level(b1.root(), visit);
    // cout << endl;
}
template<typename T>
void insert_avl(AVL<T>& avl1)
{
    cout << avl1.insert(42)->data << endl;
    cout << avl1.insert(8)->data << endl;
    cout << avl1.insert(16)->data << endl;
}

template<typename T, typename VST>
void trav_avl(AVL<T>& avl1, VST& visit)
{
    cout << "avl in trav" << endl;
    avl1.trav_in(avl1.root(), visit);
    cout << endl;

    avl1.remove(42);
    cout << "avl in trav" << endl;
    avl1.trav_in(avl1.root(), visit);
    cout << endl;
}

int main()
{
    btree<int> tree1;
    print<int> p;
    BST<int> b1;
    AVL<int> avl1;

    // insert(tree1);
    // trav(tree1, p);
    // isnert_bst(b1);
    // trav_bst(b1, p);
    insert_avl(avl1);
    trav_avl(avl1, p);

    return 0;
}

