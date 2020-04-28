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
    
    int r = _order / 2; // 取中点
    BTNodePosi(T) u = new BTNode<T>();
    for (int i = 0; i < _order - r - 1; i++)
    {
        u->child.insert(i, v->child.remove(r + 1));
        u->key.insert(i, v->key.remove(r + 1));
    }
    // child 比 key 多一个，移动剩下的 child
    u->child[_order - r - 1] = v->child.remove(r + 1);
    if(u->child[0]) // 把 u 设置为 u 内部 child 的父亲
    {
        for(int i = 0; i < u->child.size(); i++)
            u->child[i]->parent = u;
    }
    BTNodePosi(T) p = v->parent;    // 验证 v 是否是根节点
    if(!p)
    {
        _root = p = new BTNode<T>();    // 如果是根节点，将当前的根节点设置为 v 
        p->child[0] = v;
        v->parent = p;
    }
    // incomplete
    int s = p->key.search(v->key[r]) + 1;   // 在 p 的 key 中搜索 v 中要上移的 key
    p->key.insert(s, v->key.remove(r)); // 删除 v 中要上移的 key ，并插入到 p 的 key 中
    p->child.insert(s + 1, u);  // 把 u 插入到 p 的 child 中
    u->parent = p;
    overflow(p);    // 向上处理上溢
}

template<typename T>
void BTree<T>::underflow(BTNodePosi(T) v)  // 处理下溢
{

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
    bnodePosi(T) x = search(e);
    if(!x)   return false;
    int r = x->key.search(e);
    // 查找 x 的直接后继
    if(x->child[0]) // 判断 x 是不是叶子节点
    {
        bnodePosi(T) u = x->child[r + 1];
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