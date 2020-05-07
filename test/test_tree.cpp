#include <iostream>
#include"../bintree.hpp"
#include"../bst.hpp"
#include"../avl.hpp"
#include "../splay.hpp"
#include"../redblack.hpp"

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
void insert(bintree<T>& t)
{
    t.insertAsRoot(0);
    t.insertAsLc(t.root(), 1);
    t.insertAsRc(t.root(), 2);
    t.insertAsLc(t.root()->lchild, 3);
    t.insertAsLc(t.root()->rchild, 4);
    t.insertAsRc(t.root()->rchild, 5);
}

template <typename T, typename VST>
void trav(bintree<T>& t, VST& visit)
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
void test_bintree(void)
{
    bintree<int> tree1;
    print<int> p;

    insert(tree1);
    trav(tree1, p);
}

template<typename T>
void isnert_bst(BST<T>& b1)
{
    // cout << b1.insert(42)->data << endl;
    BinNodePosi(int) t1 = b1.insert(42);
    BinNodePosi(int) t2 = b1.insert(8);
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

void test_bst(void)
{
    BST<int> b1;
    print<int> p;

    isnert_bst(b1);
    trav_bst(b1, p);
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

void test_avl(void)
{
    AVL<int> avl1;
    print<int> p;

    insert_avl(avl1);
    trav_avl(avl1, p);
}

template<typename T>
void insert_splay(Splay<T>& s1)
{
    cout << s1.insert(42)->data << endl;
    cout << s1.insert(8)->data << endl;
    cout << "inserted" << endl;
}
template<typename T, typename VST>
void trav_splay(Splay<T>& s1, VST& visit)
{
    cout << "in trav" << endl;
    s1.trav_in(s1.root(), visit);
    cout << "in trav complete" << endl;
}

void test_splay(void)
{
    print<int> visit;
    cout << "splay" << endl;
    Splay<int> s1;

    insert_splay(s1);
    trav_splay(s1, visit);
    cout << "in trav" << endl;
    s1.trav_in(s1.root(), visit);
    cout << "in trav complete" << endl;
}

void test_rbtree(void)
{
}

int main()
{
    test_bintree();
    test_bst();
    test_avl();
    test_splay();
    // print<int> visit;
    // cout << "splay" << endl;
    // Splay<int> s1;

    // insert_splay(s1);
    // trav_splay(s1, visit);
    // cout << "in trav" << endl;
    // s1.trav_in(s1.root(), visit);
    // cout << "in trav complete" << endl;

    return 0;
}

