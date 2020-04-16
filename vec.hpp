#include "vec.h"

template <typename T>
vec<T>::vec(int c, int s, T v)
{
    _elem = new T[_capacity = c];
    _size = 0;
}

template <typename T>
vec<T>::vec(vec<T> const & v)
{   copy_from(v._elem, 0, v._size);  }

template <typename T>
vec<T>::vec(vec<T> const & v, int lo, int hi)
{   copy_from(v._elem, lo, hi);   }

template <typename T>
vec<T>::vec(T * a, int lo, int hi)
{   copy_from(a, lo, hi);   }

template <typename T>
vec<T>::~vec()
{   delete [] _elem;    }

template <typename T>
void vec<T>::copy_from(T * a, int lo, int hi)
{
    _elem = new T[_capacity = ((hi - lo) << 1)];
    _size = 0;
    while(lo < hi)
        _elem[_size++] = a[lo++];
}

template <typename T>
int vec<T>::size() const
{   return _size;   }

template <typename T>
int vec<T>::capacity() const
{   return _capacity;   }

template <typename T>
T & vec<T>::get(int r) const
{   return _elem[r];    }

template <typename T>
void vec<T>::put(int r, const T& e)
{   _elem[r] = e;   }

template <typename T>
void vec<T>::expand()
{
    if(_size + 1 < _capacity)
        return;
    T * old_elem = _elem;
    _elem = new T[_capacity <<= 1];
    for(int i = 0; i < _size; i++)
        _elem[i] = old_elem[i];
    delete [] old_elem;
}

template <typename T>
void vec<T>::shrink()
{
    if((_size << 1) >= _capacity)
        return;
    T * old_elem = _elem;
    _elem = new T[_capacity = (_size << 1)];
    for(int i = 0; i < _size; i++)
        _elem[i] = old_elem[i];
    delete [] old_elem;
}

template <typename T>
int vec<T>::insert(int r, const T& e)
{
    expand();
    for(int i = _size - 1; i >= r; i--)
        _elem[i + 1] = _elem[i];
    _size++;
    _elem[r] = e;
    return r;
}

template<typename T>
int vec<T>::insert(const T& e)
{   return insert(_size, e);    }

template <typename T>
T vec<T>::remove(int r)
{
    T ret = _elem[r];
    for(int i = r; i < _size - 1; i++)
        _elem[i] = _elem[i + 1];
    _size--;
    return ret;
}

template <typename T>
int vec<T>::remove(int lo, int hi)
{
    if(lo == hi)
        return 0;
    while(hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

template <typename T>
bool vec<T>::is_increase(const T& x, const T& y)
{   return x > y;   }

template <typename T>
int vec<T>::disorder(bool increase) const
{
    int count = 0;
    for(int i = 1; i < _size; i++)
        if(is_increase(_elem[i - 1], _elem[i]) == increase)
            count++;
    return count;
}

template<typename T>
int vec<T>::find(const T& e, int lo, int hi) const
{
    int i = 0;
    for(i = lo; _elem[i] != e && i < hi; i++);
    return i == hi ? -1 : i;
}

template <typename T>
int vec<T>::deduplicate()
{
    int old_size = _size;
    for(int i = 1; i < _size;)
        find(_elem[i], 0, i) < 0 ? i++ : remove(i);
    return old_size - _size;
}

template <typename T>
template <typename VST>
void vec<T>::traverse(VST & visit) const
{
    for(int i = 0; i < _size; i++)
        visit(_elem[i]);
}

template <typename T>
int vec<T>::search(T e, int lo, int hi)
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

template <typename T>
void vec<T>::swap(int x, int y)
{
    T e = _elem[x];
    _elem[x] = _elem[y];
    _elem[y] = e;
}

template <typename T>
int vec<T>::bubble(int lo, int hi)
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

template <typename T>
void vec<T>::bubble_sort(int lo, int hi)
{   while(lo < (hi = bubble(lo, hi)));  }

template <typename T>
void vec<T>::merge(int lo, int mi, int hi)
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
template <typename T>
void vec<T>::merge_sort(int lo, int hi)
{
    if(lo + 1 >= hi) return;
    int mi = (lo + hi) >> 1;
    merge_sort(lo, mi);
    merge_sort(mi, hi);
    merge(lo, mi, hi);
}

template <typename T>
void vec<T>::sort(int lo, int hi)
{
    // bubble_sort(lo, hi);
    merge_sort(lo, hi);
}

template <typename T>
T& vec<T>::operator[](int r) const
{   return _elem[r];    }