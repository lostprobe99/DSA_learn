#ifndef _BINTREE_H_
#define _BINTREE_H_

#include<stdlib.h>
#include"stack.hpp"
#include"queue.hpp"
#define BinNodePosi(T) BinNode<T>*

typedef enum { RB_RED, RB_BLACK}    RBColor;

template <typename T>
struct BinNode
{
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lchild;
    BinNodePosi(T) rchild;
    int height;
    int npl;    // 左式堆 Null Path Length
    RBColor color;

    BinNode()
    : parent(NULL), lchild(NULL), rchild(NULL), height(0), npl(1), color(RB_RED)
    {}

    BinNode(T const & e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED)
    : data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c)
    {} 

    int          size() const;
    BinNodePosi(T) succ()// 取得当前节点的直接后继
    {
        BinNodePosi(T) s = this;
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
    BinNodePosi(T) insertAsLc(T const & e);
    BinNodePosi(T) insertAsRc(T const & e);
};

template<typename T>
inline bool is_root(BinNodePosi(T) x)
{   return !(x->parent);  }

template<typename T>
inline bool is_lchild(BinNodePosi(T) x)
{   return !is_root(x) && (x == x->parent->lchild);  }

template<typename T>
inline bool is_rchild(BinNodePosi(T) x)
{   return !is_root(x) && (x == x->parent->rchild);  }

template<typename T>
inline bool has_parent(BinNodePosi(T) x)
{   return !is_root(x); }

template<typename T>
inline bool has_lchild(BinNodePosi(T) x)
{   return (x->lchild); }

template<typename T>
inline bool has_rchild(BinNodePosi(T) x)
{   return (x->rchild); }

template<typename T>
inline bool has_child(BinNodePosi(T) x)
{   return has_lchild(x) || has_rchild(x); }

template<typename T>
inline bool has_bothchild(BinNodePosi(T) x)
{   return has_lchild(x) && has_rchild(x); }

template<typename T>
inline BinNodePosi(T)& from_parent_to(BinNodePosi(T)& x)
{   return (is_root(x) ? x : (is_lchild(x) ? x->parent->lchild : x->parent->rchild));   }

template <typename T>
class bintree
{
protected:
    int _size;
    BinNodePosi(T) _root;
    virtual int update_height(BinNodePosi(T) x);
    template<typename VST>
    void visit_left_branch(BinNodePosi(T) x, VST& visit, stack<BinNodePosi(T)>& s);
    void to_left_bottom(BinNodePosi(T) x, stack<BinNodePosi(T)>& s);
public:
    bintree() : _size(0), _root(NULL) {}
    ~bintree();
    int          size() const;
    int          remove(BinNodePosi(T) x);
    bool         is_empty() const;
    void         update_height_above(BinNodePosi(T) x);
    BinNodePosi(T) root() const;
    BinNodePosi(T) insertAsRoot(const T& e);
    BinNodePosi(T) insertAsRc(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) insertAsLc(BinNodePosi(T) x, T const &e);
    BinNodePosi(T) attachAsRc(BinNodePosi(T) x, bintree<T>*& S);
    BinNodePosi(T) attachAsLc(BinNodePosi(T) x, bintree<T>*& S);
    template<typename VST>
    void trav_pre(BinNodePosi(T) x, VST visit);
    template<typename VST>
    void trav_pre_loop_I(BinNodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_pre_loop_II(BinNodePosi(T) x, VST& visit);

    template<typename VST>
    void trav_in(BinNodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_in_loop_I(BinNodePosi(T) x, VST& visit);
    template<typename VST>
    void trav_level(BinNodePosi(T) x, VST& visit);
};

#include<algorithm>
template <typename T>
int BinNode<T>::size() const
{
    int n = 1;
    if(rchild)
        n += rchild->size();
    if(lchild)
        n+= lchild->size();
    return n;
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLc(T const & e)
{   return lchild = new BinNode(e, this); }

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRc(T const & e)
{   return rchild = new BinNode(e, this); }

template <typename T>
inline int get_height(BinNodePosi(T) x)
{   return x ? x->height : -1;  }

template <typename T>
bintree<T>::~bintree()
{
    if(0 < _size)
        remove(_root);
}

template <typename T>
BinNodePosi(T) bintree<T>::insertAsRoot(const T& e)
{
    _size = 1;
    return _root = new BinNode<T>(e);
}

template <typename T>
int bintree<T>::remove(BinNodePosi(T) x)
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
inline int bintree<T>::update_height(BinNodePosi(T) x)
{
    return x->height = 1 +
        std::max(get_height(x->lchild), get_height(x->rchild));
}

template <typename T>
void bintree<T>::update_height_above(BinNodePosi(T) x)
{
    while(x)
    {
        update_height(x);
        x = x->parent;
    }
}

template <typename T>
inline int bintree<T>::size() const
{   return _size;   }

template <typename T>
inline bool bintree<T>::is_empty() const
{   return !_root;  }

template <typename T>
inline BinNodePosi(T) bintree<T>::root() const
{   return _root;  }

template <typename T>
BinNodePosi(T) bintree<T>::insertAsRc(BinNodePosi(T) x, T const &e)
{
    _size++;
    x->insertAsRc(e);
    update_height_above(x);
    return x->rchild;
}

template <typename T>
BinNodePosi(T) bintree<T>::insertAsLc(BinNodePosi(T) x, T const &e)
{
    _size++;
    x->insertAsLc(e);
    update_height_above(x);
    return x->lchild;
}
template<typename T>
BinNodePosi(T) bintree<T>::attachAsRc(BinNodePosi(T) x, bintree<T>*& S)
{
    if(x->rchild = S->_root)    x->rchild->parent = x;
    _size += S->_size;
    update_height_above(x);
    S->_root = NULL;
    S->_size = 0;
    S = NULL;
    return x;
}
template<typename T>
BinNodePosi(T) bintree<T>::attachAsLc(BinNodePosi(T) x, bintree<T>*& S)
{
    if(x->lchild = S->_root)    x->lchild->parent = x;
    _size += S->_size;
    update_height_above(x);
    S->_root = NULL;
    S->_size = 0;
    S = NULL;
    return x;
}

template <typename T>
template <typename VST>
void bintree<T>::trav_pre(BinNodePosi(T) x, VST visit)
{
    if(!x)  return;
    visit(x->data);
    trav_pre(x->lchild, visit);
    trav_pre(x->rchild, visit);
}

template <typename T>
template<typename VST>
void bintree<T>::trav_pre_loop_I(BinNodePosi(T) x, VST& visit)
{
    stack<BinNodePosi(T)> s;
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
void bintree<T>::visit_left_branch(BinNodePosi(T) x, VST& visit, stack<BinNodePosi(T)>& s)
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
void bintree<T>::trav_pre_loop_II(BinNodePosi(T) x, VST& visit)
{
    stack<BinNodePosi(T)> s;
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
void bintree<T>::trav_in(BinNodePosi(T) x, VST& visit)
{
    if(!x)  return;
    trav_in(x->lchild, visit);
    visit(x->data);
    trav_in(x->rchild, visit);
}

template<typename T>
void bintree<T>::to_left_bottom(BinNodePosi(T) x, stack<BinNodePosi(T)>& s)
{
    while(x)
    {
        s.push(x);
        x = x->lchild;
    }
}

template <typename T>
template<typename VST>
void bintree<T>::trav_in_loop_I(BinNodePosi(T) x, VST& visit)
{
    stack<BinNodePosi(T)> s;

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
void bintree<T>::trav_level(BinNodePosi(T) x, VST& visit)
{
    queue<BinNodePosi(T)> q;
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
