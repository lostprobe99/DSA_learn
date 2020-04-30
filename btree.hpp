#ifndef _BTREE_HPP_
#define _BTREE_HPP_

#include"vec.hpp"

#define BTNodePosi(T) BTNode<T>*

template<typename T> struct BTNode
{
    BTNodePosi(T) parent;
    vec<T> key;
    vec<BTNodePosi(T)> child;

    BTNode() : parent(NULL)
    {   child.insert(0, NULL);  }

    BTNode(const T& e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL)
    {
        parent = NULL;
        key.insert(0, e);
        child.insert(0, lc);
        child.insert(1, rc);
        if(lc)  lc->parent = this;
        if(rc)  rc->parent = this;
    }
};

template<typename T> class BTree
{
protected:
    int _size;
    int _order;
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot;
    void overflow(BTNodePosi(T));   // 处理上溢
    void underflow(BTNodePosi(T));  // 处理下溢
public:
    BTree(int order = 3) : _size(0), _order(order), _hot(NULL) 
    {   _root = new BTNode<T>();}
    ~BTree()
    {   if(_root)  delete _root;    }
    BTNodePosi(T)& search(const T& e);
    bool           insert(const T& e);
    bool           remove(const T& e);

    int            size() const;
    int            order() const;
    BTNodePosi(T)  root() const;
    bool           empty() const;
};

template<typename T>
inline int BTree<T>::size() const
{   return _size;   }

template <typename T>
inline int BTree<T>::order() const
{   return _order;  }

template <typename T>
inline BTNodePosi(T) BTree<T>::root() const
{   return _root;   }

template <typename T>
inline bool BTree<T>::empty() const
{   return !_root;  }

template<typename T>
void BTree<T>::overflow(BTNodePosi(T) v)   // 处理上溢
{
    if(_order >= v->child.size())   // 未发生上溢
        return;
    int s = _order / 2; // 发生上溢时，必有 _order = v->key.size()
    BTNodePosi(T) u = new BTNode<T>();
    // move v->key[s + 1, key.size() - 1] to u->key
    for(int i = 0; i < _order - s - 1; i++)
    {
        u->key.insert(i, v->key.remove(s + 1));
        u->child.insert(i, v->child.remove(s + 1));
    }
    u->child[_order - s  1] = v->child.remove(s + 1);
    if(u->child[0])
    {
        for(int i = 0; i < u->child.size(); i++)
            u->child[i]->parent = u;
    }
    BTNodePosi(T) p = v->parent;
    if(!p)
    {
        _root = p = new BTNode<T>();
        p->child[0] = v;
        v->parent = p;
    }
    int r = 1 + p->key.search(v->key[s]);
    p->key.insert(r, v->key.remove(s));
    p->child.insert(r + 1, u);
    u->parent = p;
    overflow(p);
}

template<typename T>
void BTree<T>::underflow(BTNodePosi(T) v)  // 处理下溢
{
    if((_order + 1) / 2 <= v->key.size())   return;
    BTNodePosi(T) p = v->parent;
    if(!p)  // 此时 v 是树根
    {
        if(v->key.size() == 0 && v->child[0])   // 如果 v 没有关键码却有一个非空字节点
        {
            _root = v->child[0];
            _root->parent = NULL;
            v->child[0] = NULL;
            delete v;
        }
    }
    int r = 0;
    while(p->child[r] != v) r++;    // 在 p 中查找 v 的位置

    // 第一种情况，v 是右孩子，向左兄弟借关键码
    if(r > 0)   // v 不是第一个孩子
    {
        BTNodePosi(T) l = parent->child[r - 1];
        if((_order + 1) / 2 > l->child.size())
        {
            v->key.insert(0, p->key[r - 1]);
            p->key[r - 1] = l->key.remove(l->key.size() - 1);
            v->child.insert(0, l->child.remove(l->child.size() - 1));
            if(v->child[0])  uv->child[0]->parent = v;
            return;
        }
    }

    // 第二种情况，向右兄弟借关键码
    if(r < p->child.size() - 1) // v 不是最后一个孩子
    {
        BTNodePosi(T) r = p->child[r + 1];
        if((_order + 1) / 2 < r->child.size())
        {
            v->key.insert(v->key.size(), p->key[r]);
            p->key[r] = r->key.remove(0);
            v->child.insert(v->child.size(), r->child.remove(0));
            if(v->child[v->child.size() - 1])   v->child[v->child.size() - 1]->parent = v;
            return;
        }
    }

    // 第三种情况，左或右兄弟都无法借出，将其合并
    if(0 < r)   // 向左合并
    {
        BTNodePosi(T) l = parent->child[r - 1];
        l->key.insert(l->key.size(), p->key.remove(r - 1));
        p->child.remove(r - 1);
        l->child.insert(l->child.size(), v->child.remove(0));
        if(l->child[l->child.size() - 1])   l->child[l->child.size() - 1]->parent = l;
        // 此时，v 中 key 和 child 的长度相等
        while(!v->key.empty())
        {
            l->child.insert(l->child.size(), v->child.remove(0));
            l->key.insert(l->key.size(), v->key.remove(0));
            if(l->child[l->child.size() - 1])   l->child[l->child.size() - 1]->parent = l;
        }
        delete v;
    } else {    // 向右合并
        BTNodePosi(T) r = parent->child[r + 1];
        r->key.insert(r->key.size(, p->key.remove(r + 1)));
        p->child.remove(r + 1);
        r->child.insert(0, v->child.remove(v->child.size() - 1));
        if(r->child[0]) r->child[0]->parent = r;
        while(!v->key.empty())
        {
            r->child.insert(0, v->child.remove(0));
            r->key.insert(0, v->key.remove(0))
            if(r->child[0]) r->child[0]->parent = r;
        }
        delete v;
    }
    underflow(p);
    return;
}

template<typename T>
BTNodePosi(T)& BTree<T>::search(const T& e)
{
    BTNodePosi(T) x = _root;
    _hot = NULL;
    while(x)
    {
        int r = x->key.search(e);   
        // vec.search 返回的是不大于 e 的最大值，即 e > key[r]
        if(e == x->key[r])  return x;
        _hot = x;
        x = x->child[r + 1];
    }
    return NULL;    // 查找失败
}

template<typename T>
bool BTree<T>::insert(const T& e)
{
    BTNodePosi(T) x = search(e);
    if(x)   return false;
    int r = _hot->key.search(e);
    _hot->key.insert(r+1, e);
    _hot->child.insert(NULL);
    _size++;
    overflow(_hot);
    return true;
}

template<typename T>
bool BTree<T>::remove(const T& e)
{
    BinNodePosi(T) x = search(e);
    if(!x)   return false;
    int r = x->key.search(e);
    // 查找 x 的直接后继
    if(x->child[0]) // 判断 x 是不是叶子节点
    {
        BinNodePosi(T) u = x->child[r + 1];
        while(u->child[0])  u = u->child[0];
        x->key[r] = u->key[0];  // 用 x 直接后继的最小 key 覆盖将要删除的 e 
        x = u;  // 此时，u 中的 key[0] 成为多余的元素
        r = 0;
    }
    x->key.remove(r);   // 删除 u 中多余的 key[0]
    x->child.remove(r + 1);
    _size--;
    underflow(x);   // 处理可能存在的下溢
    return true;
}

#endif