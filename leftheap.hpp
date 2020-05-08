/*
 * @Author: lostprobe99 
 * @Date: 2020-05-08 13:24:48 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-08 15:15:34
 */
#ifndef LEFTHEAP_HPP
#define LEFTHEAP_HPP
#include"bintree.hpp"
#include"pq.h"

template<typename T>
static void swap(T& x, T& y)
{   T t = x;    x = y;  y = t;  }

// log(n)
template<typename T>
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b)
{
    if(!a)  return b;
    if(!b)  return a;
    // 确保 a >= b
    if(a->data < b->data) swap(a->data, b->data);
    // 将 a 的右子堆与 b 合并
    a->rchild = merge(a->rchild, b);
    a->rchild->parent = a;
    // 如果左堆小于右堆
    if(!a->lchild || a->lchild->npl < a->rchild->npl)
        swap(a->lchild, a->rchild);
    a->npl = a->rchild ? a->rchild->npl + 1 : 1;
    return a;
}

template<typename T>
class leftheap : public PQ<T>, public bintree<T>
{
public:
    void insert(const T&);

    T& get_max() const
    {   return this->_root->data;   }

    T del_max();
};

// log(n)
template<class T>
void leftheap<T>::insert(const T& e)
{
    BinNodePosi(T) v = new BinNode<T>(e);
    this->_root = merge(v, this->_root);
    this->_root->parent = NULL;
    this->_size++;
}

// log(n)
template<class T>
T leftheap<T>::del_max()
{
    T e = this->_root->data;
    BinNodePosi(T) lHeap = this->_root->lchild;
    BinNodePosi(T) rHeap = this->_root->rchild;
    delete this->_root;
    this->_size--;
    this->_root = merge(lHeap, rHeap);
    if(this->_root)    this->_root->parent = NULL;
    return e;
}

#endif