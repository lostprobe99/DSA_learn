#include "list.h"
#include<iostream>
using std::cout;
using std::endl;

template <typename T>
posi(T) listnode<T>::insert_as_pred(T const & e)
{
    // 创建一个数据是e，前驱是this的pred，后继是this的节点
    posi(T) x = new listnode(e, this->pred, this);
    // 当前节点的前驱的后继是x
    // 当前节点的前驱是x
    this->pred->succ = x; this->pred = x;
    return x;
}

template <typename T>
posi(T) listnode<T>::insert_as_succ(T const & e)
{
    posi(T) x = new listnode(e, this, this->succ);
    this->succ->pred = x; this->succ = x;
    return x;
}

template <typename T>
void list<T>::init()
{
    header = new listnode<T>;
    tailer = new listnode<T>;

    header->succ = tailer;
    header->pred = NULL;

    tailer->succ = NULL;
    tailer->pred = header;
    _size = 0;
}

template <typename T>
list<T>::list()
{   init();    }

template <typename T>
void list<T>::copy_node(posi(T) p, int n)
{
    while(n-- > 0)
    { insert_before(tailer, p->data); p = p->succ; }
}

template <typename T>
list<T>::list(posi(T) p, int n)
{
    init();
    copy_node(p, n);
}

template <typename T>
list<T>::list(list<T> const & l, int n)
{   init(); copy_node(l.head()->succ, n);  }

template <typename T>
list<T>::~list()
{
    clear();
    delete tailer;
    delete header;
}

template <typename T>
posi(T) list<T>::tail() const
{    return tailer; }

template <typename T>
posi(T) list<T>::head() const
{   return header;  }

template <typename T>
posi(T) list<T>::first() const
{   return header->succ;    }

template <typename T>
posi(T) list<T>::last() const
{   return tailer->pred;    }

template<typename T>
int list<T>::size() const
{   return _size;   }

// find in pred of p forward n, not include p
template <typename T>
posi(T) list<T>::find(T const &e, int n, posi(T) p) const
{
    while(n-- > 0)
        if(e == (p = p->pred)->data)  return p;
    return NULL;
}
// backward from p
template<typename T>
posi(T) list<T>::find(T const &e, posi(T) p, int n) const
{
    while(n-- > 0)
        if(e == (p = p->succ)->data)  return p;
    return NULL;
}

template <typename T>
posi(T) list<T>::insert_before(posi(T) p, T const& e)
{
    _size++;
    return p->insert_as_pred(e);
}

template <typename T>
posi(T) list<T>::insert_after (posi(T) p, T const& e)
{
    _size++;
    return p->insert_as_succ(e);
}

template <typename T>
posi(T) list<T>::search(T const &e, int n, posi(T) p) const
{
    while(0 <= n--)
    {
        if((p = p->pred)->data <= e)
            break;
    }
    return p;
}

template <typename T>
void list<T>::show() const
{
    posi(T) now = header->succ;
    while(now != tailer)
    {
        cout << now->data << " ";
        now = now->succ;
    }
    cout << endl;
}

template <typename T>
T   list<T>::remove(posi(T) p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template <typename T>
int list<T>::clear()
{
    int old_size = _size;
    while(_size > 0)
        remove(header->succ);
    return old_size;
}

template <typename T>
int list<T>::deduplicate()
{
    int old_size = _size;
    if(_size < 2)
        return 0;
    posi(T) p = header->succ;
    int r = 1;
    while(tailer != (p = p->succ))
    {
        posi(T) q = find(p->data, r, p);
        // q ? remove(q) : r++;
        if(NULL == q)
            r++;
        else
            remove(q);
    }
    return old_size - _size;
}

#if 0
// 有序列表去重
template <typename T>
int list<T>::uniquify()
{
    int old_size = _size;
    posi(T) p = header->succ;
    posi(T) q;
    while(tailer != (q = p->succ))
    {
        p->data == q->data ?
            remove(q)
            : p = q;
    }
    return old_size - _size;
}
#endif

template <typename T>
posi(T) list<T>::select_max(posi(T) p, int n)
{
    posi(T) maxv = p;
    posi(T) now = p;
    for(int i = 0; i < n; i++)
    {
        if(maxv->data <= now->data)
            maxv = now;
        now = now->succ;
    }
    return maxv;
}

template <typename T>
void list<T>::swap(T & x, T & y)
{
    T t = x;
    x = y;
    y = t;
}

template <typename T>
void list<T>::selection_sort(posi(T) p, int n)
{
    posi(T) x = p;
    posi(T) y = p;
    for(int i = 0; i < n; i++)
        y = y->succ;

    while(1 < n)
    {
        swap(y->pred->data, select_max(x, n)->data);
        y = y->pred;
        n--;
    }
}

template <typename T>
void list<T>::insertion_sort(posi(T) p, int n)
{
    for(int i = 0; i < n; i++)
    {
        insert_after(search(p->data, i, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void list<T>::sort(posi(T) p, int n)
{
    // selection_sort(p, n);
    insertion_sort(p, n);
}

template <typename T>
bool list<T>::empty() const
{   return header->succ == tailer ? true : false;   }
