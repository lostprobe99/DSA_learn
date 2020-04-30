/* binary search tree */
#ifndef _BST_HPP_
#define _BST_HPP_

#include"bintree.hpp"

template<typename K, typename V> struct Entry{
    K key; V value;
    Entry(K k = K(), V v = V()) : key(k), value(v) {}
    Entry(const Entry<K, V>& e) : key(e.key), value(e.value) {}

    bool operator<  (const Entry<K, V>& e) {    return key < e.key;     }
    bool operator>  (const Entry<K, V>& e) {    return key > e.key;     }
    bool operator<= (const Entry<K, V>& e) {    return key <= e.key;    }
    bool operator>= (const Entry<K, V>& e) {    return key >= e.key;    }
};

template<typename T> class BST : public bintree<T>
{
protected:
    BinNodePosi(T) _hot;
    BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
    BinNodePosi(T) rotateAt(BinNodePosi(T));
public:
    BinNodePosi(T) hot()
    {   return _hot;    }
    virtual BinNodePosi(T)& search(const T&);    // 待查找的值是一个关键码，而非数据
    virtual BinNodePosi(T) insert(const T& );
    virtual bool remove(const T& e)
    {
        BinNodePosi(T) x = search(e);
        if(!x)  return false;
        removeAt(x, _hot);  // x 成为新节点，_hot 是 x 的父节点
        this->update_height_above(_hot);
        return true;
    };
};

template<typename T>
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
    if(!v || v->data == e)  return v;
    hot = v;
    while (1)
    {
        BinNodePosi(T)& c = (e < hot->data) ? hot->lchild : hot->rchild;
        if(!c || c->data == e)  return c;
        hot = c;
    }
}

template<typename T> 
inline BinNodePosi(T)& BST<T>::search(const T& e)
{   return searchIn(this->_root, e, _hot = NULL);  }

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
    BinNodePosi(T)& x = search(e);
    if(x)   return x;
    x = new BinNode<T>(e, _hot);
    this->_size++;
    this->update_height_above(x);
    return x;
}

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot)
{
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = NULL;   // 取代 x 节点的节点
    if(!x->rchild){    // 不存在右节点  // 包含了左右节点皆空的情况
        succ = x = x->lchild;
    }
    else if(!x->lchild){ // 不存在左节点
        succ = x = x->rchild;
    } else {    // 左右节点皆存在
        w = w->succ();
        std::swap(w->data, x->data);
        BinNodePosi(T) u = w->parent;
        // 代表 w 是 u 的右子节点，否则就是左子节点，因为如果 w 是 u 的左子节点，那么 w 就不可能是 x 的 succ()
        (u == x ? u->rchild : u->lchild) = succ = w->rchild;  // succ() 只有右孩子
    }
    hot = w->parent;
    if(succ) succ->parent = hot;
    // delete w->data; // 原本的 x 节点
    delete w;
    return succ;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, \
    BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
    a->lchild = T0; if(T0)  T0->parent = a;
    a->rchild = T1; if(T1)  T1->parent = a;
    this->update_height(a);
    c->lchild = T2; if(T2)  T2->parent = a;
    c->rchild = T3; if(T3)  T3->parent = a;
    this->update_height(c);
    b->lchild = a;  a->parent = b;
    b->rchild = c;  c->parent = b;
    this->update_height(b);
    return b;
}

template<typename T>
inline BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v)
{
    BinNodePosi(T) p = v->parent; 
    BinNodePosi(T) g = p->parent;
    if(is_lchild(p))
    {
        if(is_lchild(v)){
            p->parent = g->parent;  // 确立变换后的局部根节点
            return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
        }
        else{
            v->parent = g->parent;
            return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
        }
    }
    else
    {
        if(is_rchild(v)){
            p->parent = g->parent;
            return connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
        }
        else{
            v->parent = g->parent;
            return connect34(g, v, g, g->lchild, v->lchild, v->rchild, p->rchild);
        }
    }
}

#endif