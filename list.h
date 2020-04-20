#ifndef _LIST_H_
#define _LIST_H_

#include<stdlib.h>

#define posi(T) listnode<T>*
template <typename T>
struct listnode
{
    T data;
    posi(T) succ;
    posi(T) pred;
    listnode(){}
    listnode(T e, posi(T) pre = NULL, posi(T) nxt = NULL)
    : data(e), pred(pre), succ(nxt)
    {}
    posi(T) insert_as_pred(T const & e);
    posi(T) insert_as_succ(T const & e);
};

template <typename T>
class list
{
private:
    int     _size;
    posi(T) header;
    posi(T) tailer;
    void    init();
    void    copy_node(posi(T) p, int n);
    void    selection_sort(posi(T) p, int n);
    posi(T) select_max(posi(T) p, int n);
    void    insertion_sort(posi(T) p, int n);
    void    swap(T & x, T & y);
public:
    list();
    list(posi(T) p, int n);
    list(list<T> const & l, int n);
    ~list();
    posi(T) tail() const;
    posi(T) head() const;
    posi(T) first() const;
    posi(T) last() const;
    posi(T) find(T const &e, int n, posi(T) p) const;
    posi(T) find(T const &e, posi(T) p, int n) const;
    posi(T) insert_before(posi(T) p, T const& e);
    posi(T) insert_after (posi(T) p, T const& e);
    posi(T) search(T const &e, int n, posi(T) p) const;
    int     size() const;
    void    show() const;
    T       remove(posi(T) p);
    int     clear();
    int     deduplicate();
    void    sort(posi(T) p, int n);
    bool    empty() const;
#if 0
    int     uniquify(); // 有序列表去重
#endif
};

#endif
