/*
 * @Author: lostprobe99 
 * @Date: 2020-05-07 17:48:04 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-07 21:13:12
 */
/* 完全二叉堆 */
#ifndef _PQ_COMPLHEAP_HPP_
#define _PQ_COMPLHEAP_HPP_
#include"pq.h"
#include"vec.hpp"

template<typename T> class pq_ComplHeap : public PQ<T>, public vec<T> 
{
private:
    inline int parent(int i)
    {   return (i - 1) >> 1;}
    inline int rchild(int i)
    {   return (i << 1) + 1;}
    inline int lchild(int i)
    {   return (i + 1) << 1;}
    inline bool inheap(int n, int i)
    {   return (-1 < i) && (i < n); }
    inline int lastInternal(int i)
    {   return parent(i);   }
    inline int proper_parent(int n, int i)
    {
        return inheap(n, rchild(i)) ? max(i, max(rchild(i), lchild(i))) :
                inheap(n, lchild(i)) ? max(i, lchild(i)) : i;
    }
    inline int max(int i, int j)
    {   return this->_elem[i] > this->_elem[j] ? i : j; }
protected:
    int percolate_down(int n, int i)
    {
        int j = i;
        while(i != (j = proper_parent(n, i)))
        {   this->swap(i, j); i = j;  }
        return i;
    }
    int percolate_up(int i)
    {
        while(this->_elem[i] > this->_elem[parent(i)])
        {   this->swap(i, parent(i)); i = parent(i);  }
        return i;
    }
    // 高度大的节点更少，这一部分消耗的效率更少
    // Floyd 法，自下而上，效率相当于 所有节点高度的和
    void heapify(int n)
    {
        for(int i = n / 2 - 1; inheap(n, i); i--)
            percolate_down(n, i);
    }
    #if 0
    // 深度高的节点更多，占据了大量效率
    // 蛮力法，自上而下，效率相当于 所有节点深度的和
    void heapify(int n)
    {
        for(int i = 0; i < this->_size; i++)
            percolate_up(i);
    }
    #endif
public:
    explicit pq_ComplHeap() {}

    explicit pq_ComplHeap(T * A, int n)
    {   this->copy_from(A, 0, n); heapify(n);  }

    void insert(const T& e)
    {   vec<T>::insert(e);  percolate_up(this->_size - 1); }

    T& get_max() const
    {   return this->_elem[0];    }

    T del_max()
    {
        T max_elem = this->_elem[0];
        this->_elem[0] = this->_elem[--this->_size];
        percolate_down(this->_size, 0);
        return max_elem;
    }
};

#endif