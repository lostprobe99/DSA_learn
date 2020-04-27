#ifndef _BTREE_HPP_
#define _BTREE_HPP_

#include"vec.hpp"

#define BTNodePosi(T) BTNode<T>*

template<typename T> struct BTNode
{
    BTNodePosi(T) parent;
    vec<T> key;
    vec<BTNodePosi(T)> child;

    BTNode() : parent(NULL)
    {   child.insert(0, NULL);  }

    BTNode(const T& e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL)
    {
        parent = NULL;
        key.insert(0, e);
        child.insert(0, lc);
        child.insert(1, rc);
        if(lc)  lc->parent = this;
        if(rc)  rc->parent = this;
    }
};

template<typename T> class BTree
{
protected:
    int _size;
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;
    void overflow(BTNodePosi(T));   // 处理上溢
    void underflow(BTNodePosi(T));  // 处理下溢
public:
    BTNodePosi(T)& search(const T& e);
    bool insert(const T& e);
    bool remove(const T& e);
};

#endif