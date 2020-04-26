#ifndef _BTREE_H_
#define _BTREE_H_

#include<stdlib.h>
#include"stack.hpp"
#include"queue.hpp"
#define bnodePosi(T) bnode<T>*

template <typename T>
struct bnode
{
    T data;
    bnodePosi(T) parent;
    bnodePosi(T) lchild;
    bnodePosi(T) rchild;
    int height;

    bnode()
    : parent(NULL), lchild(NULL), rchild(NULL), height(0)
    {}

    bnode(T const & e, bnodePosi(T) p = NULL, bnodePosi(T) lc = NULL, bnodePosi(T) rc = NULL, int h = 0)
    : data(e), parent(p), lchild(lc), rchild(rc), height(h)
    {} 

    int          size() const;
    bnodePosi(T) succ()// 取得当前节点的直接后继
    {
        bnodePosi(T) s = this;
        if(s->rchild)
        {
            s = s->rchild;
            while(s->lchild)    s = s->lchild;
        }
        else
        {
            while(s->parent->rchild == s)   s = s->parent;
            s = s->parent;
        }
        return s;
    }
    bnodePosi(T) insertAsLc(T const & e);
    bnodePosi(T) insertAsRc(T const & e);
};

template<typename T>
inline bool is_root(bnodePosi(T) x)
{   return !(x->parent);  }

template<typename T>
inline bool is_lchild(bnodePosi(T) x)
{   return !is_root(x) && (x == x->parent->lchild);  }

template<typename T>
inline bool is_rchild(bnodePosi(T) x)
{   return !is_root(x) && (x == x->parent->rchild);  }

template<typename T>
inline bool has_parent(bnodePosi(T) x)
{   return !is_root(x); }

template<typename T>
inline bool has_lchild(bnodePosi(T) x)
{   return (x->lchild); }

template<typename T>
inline bool has_rchild(bnodePosi(T) x)
{   return (x->rchild); }

template<typename T>
inline bool has_child(bnodePosi(T) x)
{   return has_lchild(x) || has_rchild(x); }

template<typename T>
inline bool has_bothchild(bnodePosi(T) x)
{   return has_lchild(x) && has_rchild(x); }

template<typename T>
inline bnodePosi(T)& from_parent_to(bnodePosi(T)& x)
{   return (is_root(x) ? x : (is_lchild(x) ? x->parent->lchild : x->parent->rchild));   }

template <typename T>
class btree
{
protected:
    int _size;
    bnodePosi(T) _root;
    virtual int update_height(bnodePosi(T) x);
    template<typename VST>
    void visit_left_branch(bnodePosi(T) x, VST& visit, stack<bnodePosi(T)>& s);
    void to_left_bottom(bnodePosi(T) x, stack<bnodePosi(T)>& s);
public:
    btree() : _size(0), _root(NULL) {}
    ~btree();
    int          size() const;
    int          remove(bnodePosi(T) x);
    bool         is_empty() const;
    void         update_height_above(bnodePosi(T) x);
    bnodePosi(T) root() const;
    bnodePosi(T) insertAsRoot(const T& e);
    bnodePosi(T) insertAsRc(bnodePosi(T) x, T const &e);
    bnodePosi(T) insertAsLc(bnodePosi(T) x, T const &e);
    template<typename VST>
    void trav_pre(bnodePosi(T) x, VST visit);
    template<typename VST>
    void trav_pre_loop_I(bnodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_pre_loop_II(bnodePosi(T) x, VST& visit);

    template<typename VST>
    void trav_in(bnodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_in_loop_I(bnodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_level(bnodePosi(T) x, VST& visit);
};

#include<algorithm>
template <typename T>
int bnode<T>::size() const
{
    int n = 1;
    if(rchild)
        n += rchild->size();
    if(lchild)
        n+= lchild->size();
    return n;
}

template <typename T>
bnodePosi(T) bnode<T>::insertAsLc(T const & e)
{   return lchild = new bnode(e, this); }

template <typename T>
bnodePosi(T) bnode<T>::insertAsRc(T const & e)
{   return rchild = new bnode(e, this); }

template <typename T>
inline int get_height(bnodePosi(T) x)
{   return x ? x->height : -1;  }

template <typename T>
btree<T>::~btree()
{
    if(0 < _size)
        remove(_root);
}

template <typename T>
bnodePosi(T) btree<T>::insertAsRoot(const T& e)
{
    _size = 1;
    return _root = new bnode<T>(e);
}

template <typename T>
int btree<T>::remove(bnodePosi(T) x)
{
    if(!x)  return 0;

    if(x != _root && x->parent->rchild == x)
        x->parent->rchild = NULL;
    if(x != _root && x->parent->lchild == x)
        x->parent->lchild = NULL;

    update_height_above(x->parent);

    int n = 1 + remove(x->lchild) + remove(x->rchild);
    delete x;
    _size -= n;
    return n;
}

template <typename T>
inline int btree<T>::update_height(bnodePosi(T) x)
{
    return x->height = 1 +
        std::max(get_height(x->lchild), get_height(x->rchild));
}

template <typename T>
void btree<T>::update_height_above(bnodePosi(T) x)
{
    while(x)
    {
        update_height(x);
        x = x->parent;
    }
}

template <typename T>
inline int btree<T>::size() const
{   return _size;   }

template <typename T>
inline bool btree<T>::is_empty() const
{   return !_root;  }

template <typename T>
inline bnodePosi(T) btree<T>::root() const
{   return _root;  }

template <typename T>
bnodePosi(T) btree<T>::insertAsRc(bnodePosi(T) x, T const &e)
{
    _size++;
    x->insertAsRc(e);
    update_height_above(x);
    return x->rchild;
}

template <typename T>
bnodePosi(T) btree<T>::insertAsLc(bnodePosi(T) x, T const &e)
{
    _size++;
    x->insertAsLc(e);
    update_height_above(x);
    return x->lchild;
}

template <typename T>
template <typename VST>
void btree<T>::trav_pre(bnodePosi(T) x, VST visit)
{
    if(!x)  return;
    visit(x->data);
    trav_pre(x->lchild, visit);
    trav_pre(x->rchild, visit);
}

template <typename T>
template<typename VST>
void btree<T>::trav_pre_loop_I(bnodePosi(T) x, VST& visit)
{
    stack<bnodePosi(T)> s;
    s.push(x);
    while(!s.empty())
    {
        x = s.pop();
        visit(x->data);
        if(NULL != x->rchild)
            s.push(x->rchild);
        if(NULL != x->lchild)
            s.push(x->lchild);
    }
}

template<typename T>
template<typename VST>
void btree<T>::visit_left_branch(bnodePosi(T) x, VST& visit, stack<bnodePosi(T)>& s)
{
    while(x)
    {
        visit(x->data);
        s.push(x->rchild);
        x = x->lchild;
    }
}

template<typename T>
template<typename VST>
void btree<T>::trav_pre_loop_II(bnodePosi(T) x, VST& visit)
{
    stack<bnodePosi(T)> s;
    while(true)
    {
        visit_left_branch(x, visit, s);
        if(s.empty())
            break;
        x = s.pop();
    }
}

template <typename T>
template<typename VST>
void btree<T>::trav_in(bnodePosi(T) x, VST& visit)
{
    if(!x)  return;
    trav_in(x->lchild, visit);
    visit(x->data);
    trav_in(x->rchild, visit);
}

template<typename T>
void btree<T>::to_left_bottom(bnodePosi(T) x, stack<bnodePosi(T)>& s)
{
    while(x)
    {
        s.push(x);
        x = x->lchild;
    }
}

template <typename T>
template<typename VST>
void btree<T>::trav_in_loop_I(bnodePosi(T) x, VST& visit)
{
    stack<bnodePosi(T)> s;

    while(true)
    {
        to_left_bottom(x, s);
        if(s.empty())
            break;
        x = s.pop();
        visit(x->data);
        x = x->rchild;
    }
}

template<typename T>
template<typename VST>
void btree<T>::trav_level(bnodePosi(T) x, VST& visit)
{
    queue<bnodePosi(T)> q;
    q.enqueue(x);
    while(!q.empty())
    {
        x = q.dequeue();
        visit(x->data);
        if(x->lchild)
            q.enqueue(x->lchild);
        if(x->rchild)
            q.enqueue(x->rchild);
    }
}


#endif
