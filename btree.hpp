#include"btree.h"
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
int btree<T>::update_height_above(bnodePosi(T) x)
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
