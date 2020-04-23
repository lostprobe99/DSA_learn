/* binary search tree */
#include"btree.hpp"
#ifndef _BST_HPP_
#define _BST_HPP_

template<typename K, typename V> struct Entry{
    K key; V value;
    Entry(K k = K(), V v = V()) : key(k), value(v) {}
    Entry(const Entry<K, V>& e) : key(e.key), value(e.value) {}

    bool operator<  (const Entry<K, V>& e) {    return key < e.key;     }
    bool operator>  (const Entry<K, V>& e) {    return key > e.key;     }
    bool operator<= (const Entry<K, V>& e) {    return key <= e.key;    }
    bool operator>= (const Entry<K, V>& e) {    return key >= e.key;    }
};

template<typename T> class BST : public btree<T>
{
private:
    bnodePosi(T) _hot;
    bnodePosi(T) connect34(bnodePosi(T), bnodePosi(T), bnodePosi(T), bnodePosi(T), bnodePosi(T), bnodePosi(T), bnodePosi(T));
    static bnodePosi(T) removeAt(bnodePosi(T)&, bnodePosi(T)&);
    static bnodePosi(T)& searchIn(bnodePosi(T)&, const T&, bnodePosi(T)&);
public:
    int _size;
    bnodePosi(T) _root;
    BST() : _size(0), _root(NULL) {}
    virtual bnodePosi(T) search(const T&);    // 待查找的值是一个关键码，而非数据
    virtual bnodePosi(T) insert(const T& );
    virtual bool remove(const T& e)
    {
        bnodePosi(T) x = search(e);
        if(!x)  return false;
        removeAt(x, _hot);  // x 成为新节点，_hot 是 x 的父节点
        this->update_height_above(_hot);
        return true;
    };
};

template<typename T> 
bnodePosi(T) BST<T>::search(const T& x)
{
    bnodePosi(T) t = this->root();
    while(t)
    {
        if(x < t->data)
            t= t->lchild;
        else if(x > t->data)
            t= t->rchild;
        else
            break;
    }
    _hot = (t == NULL ? t : t->parent);
    return t;
}

template<typename T>
bnodePosi(T) BST<T>::insert(const T& e)
{
    bnodePosi(T) x = search(e);
    if(x)   return x;
    x = new bnode<T>(e, _hot);
    this->_size++;
    this->update_height_above(x);
    return x;
}

template<typename T>
bnodePosi(T) BST<T>::removeAt(bnodePosi(T)& x, bnodePosi(T)& hot)
{
    bnodePosi(T) w = x;
    bnodePosi(T) succ = NULL;   // 取代 x 节点的节点
    if(!x->rchild){    // 不存在右节点  // 包含了左右节点皆空的情况
        succ = x = x->lchild;
    }
    else if(!x->lchild){ // 不存在左节点
        succ = x = x->rchild;
    } else {    // 左右节点皆存在
        w = w->succ();
        std::swap(w->data, x->data);
        bnodePosi(T) u = w->parent;
        // 代表 w 是 u 的右子节点，否则就是左子节点，因为如果 w 是 u 的左子节点，那么 w 就不可能是 x 的 succ()
        (u == x ? u->rchild : u->lchild) = succ = w->rchild;  // succ() 只有右孩子
    }
    hot = w->parent;
    if(succ) succ->parent = hot;
    // delete w->data; // 原本的 x 节点
    delete w;
    return succ;
}

#endif