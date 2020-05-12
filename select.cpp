/*
 * @Author: lostprobe99 
 * @Date: 2020-05-12 12:13:58 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-12 12:55:13
 */
#include"vec.hpp"

template<typename T>
class Selector{
public:
    int c;
    T maj;
    Selector() : c(0){}
    void operator()(T& e)
    {
        if(!c)
        {
            maj = e;
            c = 1;
        }
        else
            maj == e ? c++ : c--;
    }
};

template<typename T>
bool majority_check(const vec<T>& v, T maj)
{
    int o = 0;
    for(int i = 0; i < v.size(); i++)
        if(v[i] == maj)
            o++;
    return o << 1 > v.size();
}

// 选出出现次数超过一半的数
template<typename T>
T majority_select(const vec<T>& v)
{
    T maj;
    for(int i = 0, c = 0; i < v.size(); i++)
    {
        if(c == 0) {
            maj = v[i];
            c = 1;
        } else
            maj == v[i] ? c++ : c--;
    }
    return maj;
}

template<typename T>
bool majority(const vec<T>& v, T& maj)
{
    maj = majority_select(v);
    return majority_check(v, maj);
}

template<typename T>
T majority_select_trav(const vec<T>& v)
{
    Selector<T> select;
    v.traverse(select);
    return select.maj;
}

template<typename T>
void quick_select(vec<T>& v, int k)
{
    for(int lo = 0, hi = v.size() - 1; lo < hi;)
    {
        int i = lo, j = hi; T pivot = v[i];
        while(i < j)
        {
            while((i < j) && v[j] >= pivot)
                j--;
            v[i] = v[j];    // 原 v[i] 已备份为 pivot
            while((i < j) && v[i] <= pivot)
                i++;
            v[j] = v[i];
        }   // 此时 i == j
        v[i] = pivot;   // 放置 pivot
        if(k <= i)  hi = i - 1;
        if(i <= k)  lo = i + 1;
    }   // 外循环在最好情况下可达到常数级
}