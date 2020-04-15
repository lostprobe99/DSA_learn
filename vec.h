#pragma once
#include<stdlib.h>

#define DEFAULT_CAPACITY 5

template <typename T>
class vec
{
private:
    T * _elem;
    int _size, _capacity;
    void copy_from(T * a, int lo, int hi);
    bool is_increase(T x, T y);
    void bubble_sort(int lo, int hi);
    int  bubble(int lo, int hi);
    void merge_sort(int lo, int hi);
    void merge(int lo, int mi, int hi);
public:
    vec(int c = DEFAULT_CAPACITY);
    vec(vec<T> const & v);
    vec(vec<T> const & v, int lo, int hi);
    vec(T * a, int lo, int hi);
    virtual ~vec();

    void    expand();
    void    shrink();
    int     size() const;
    int     capacity() const;
    T &     get(int r) const;
    void    put(int r, T e);
    void    insert(int r, T e);
    T       remove(int r);
    int     remove(int lo, int hi);
    int     disorder(bool increase = true) const;
    int     find(T e, int lo, int hi) const;
    int     deduplicate();
    template<typename VST>
    void    traverse(VST& visit) const;
    int     search(T e, int lo, int hi);
    void    swap(int x, int y);
    void    sort(int lo, int hi);
};
