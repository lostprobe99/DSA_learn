#ifndef _VEC_HPP_
#define _VEC_HPP_
#include<stdlib.h>
#include<string.h>
#include"pq_ComplHeap.hpp"

#define DEFAULT_CAPACITY 5

template <typename T> class vec
{
protected:
    T * _elem;
    int _size, _capacity;

    void copy_from(T * a, int lo, int hi)
    {
        _elem = new T[_capacity = ((hi - lo) << 1)];
        _size = 0;
        while(lo < hi)
            _elem[_size++] = a[lo++];
    }

    bool is_increase(const T& x, const T& y)
    {   return x > y;   }
    
    int bubble(int lo, int hi)
    {
        int last = lo;
        while(++lo < hi)
        {
            if(_elem[lo - 1] > _elem[lo])
            {
                swap(lo - 1, lo);
                last = lo;
            }
        }
        return last;
    }

    void bubble_sort(int lo, int hi)
    {   while(lo < (hi = bubble(lo, hi)));  }

    void merge(int lo, int mi, int hi)
    {
        T * A = _elem + lo;
        int lb = mi - lo, lc = hi - mi;
        T * B = new T[lb];
        for(int i = 0; i < lb; i++)
            B[i] = A[i];
        T *C = _elem + mi;
        for(int i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
        {
            if((j < lb) && (lc <= k || B[j] <= C[k]))
                A[i++] = B[j++];
            if((k < lc) && (lb <= j || B[j] > C[k]))
                A[i++] = C[k++];
        }
        delete [] B;
    }
    void merge_sort(int lo, int hi)
    {
        if(lo + 1 >= hi) return;
        int mi = (lo + hi) >> 1;
        merge_sort(lo, mi);
        merge_sort(mi, hi);
        merge(lo, mi, hi);
    }
    void heap_sort(int lo, int hi)
    {
        #if 0
        pq_ComplHeap<T> H(_elem + lo, hi - lo);
        while(!H.empty())
            _elem[--hi] = H.del_max();
        #endif
    }

public:
    vec(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        _size = 0;
    }

    vec(vec<T> const & v)
    {   copy_from(v._elem, 0, v._size);  }

    vec(vec<T> const & v, int lo, int hi)
    {   copy_from(v._elem, lo, hi);   }

    vec(T * a, int lo, int hi)
    {   copy_from(a, lo, hi);   }

    virtual ~vec()
    {   delete [] _elem;    }

    bool empty()
    {   return _size ? false : true ;}

    int size() const
    {   return _size;   }

    int capacity() const
    {   return _capacity;   }

    T & get(int r) const
    {   return _elem[r];    }

    void put(int r, const T& e)
    {   _elem[r] = e;   }

    void expand()
    {
        if(_size + 1 < _capacity)
            return;
        T * old_elem = _elem;
        _elem = new T[_capacity <<= 1];
        for(int i = 0; i < _size; i++)
            _elem[i] = old_elem[i];
        delete [] old_elem;
    }

    void shrink()
    {
        if((_size << 1) >= _capacity)
            return;
        T * old_elem = _elem;
        _elem = new T[_capacity = (_size << 1)];
        for(int i = 0; i < _size; i++)
            _elem[i] = old_elem[i];
        delete [] old_elem;
    }

    int insert(int r, const T& e)
    {
        expand();
        for(int i = _size - 1; i >= r; i--)
            _elem[i + 1] = _elem[i];
        _size++;
        _elem[r] = e;
        return r;
    }

    int insert(const T& e)
    {   return insert(_size, e);    }

    T remove(int r)
    {
        T ret = _elem[r];
        for(int i = r; i < _size - 1; i++)
            _elem[i] = _elem[i + 1];
        _size--;
        return ret;
    }

    int remove(int lo, int hi)
    {
        if(lo == hi)
            return 0;
        while(hi < _size)
            _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    } 

    int disorder(bool increase) const
    {
        int count = 0;
        for(int i = 1; i < _size; i++)
            if(is_increase(_elem[i - 1], _elem[i]) == increase)
                count++;
        return count;
    }

    int find(const T& e, int lo, int hi) const
    {
        int i = 0;
        for(i = lo; _elem[i] != e && i < hi; i++);
        return i == hi ? -1 : i;
    }

    int deduplicate()
    {
        int old_size = _size;
        for(int i = 1; i < _size;)
            find(_elem[i], 0, i) < 0 ? i++ : remove(i);
        return old_size - _size;
    }

    template <typename VST>
    void traverse(VST & visit) const
    {
        for(int i = 0; i < _size; i++)
            visit(_elem[i]);
    }

    int search(const T& e, int lo, int hi)
    {
        int mi = 0;
        while(lo + 1 < hi)
        {
            mi = (hi + lo) >> 1;
            e < _elem[mi] ? 
                hi = mi : lo = mi;
        }
        return lo;
    }

    int search(const T& e)
    {   return search(e, 0, _size); }

    // param(x, y): index of will be swaped elem
    inline void swap(int x, int y)
    {
        T e = _elem[x];
        _elem[x] = _elem[y];
        _elem[y] = e;
    }

    void sort(int lo, int hi)
    {
        // bubble_sort(lo, hi);
        // merge_sort(lo, hi);
        heap_sort(lo, hi);
    }

    T& operator[](int r) const
    {   return _elem[r];    }
};

#endif