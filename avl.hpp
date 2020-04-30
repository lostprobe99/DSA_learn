#ifndef _AVL_HPP_
#define _AVL_HPP_

#include"bst.hpp"

template<typename T>
inline BinNodePosi(T)& taller_child(BinNodePosi(T)& x)
{
    if(get_height(x->lchild) > get_height(x->rchild))
        return x->lchild;
    else if(get_height(x->lchild) < get_height(x->rchild))
        return x->rchild;
    else
        return is_lchild(x) ? x->lchild : x->rchild;
}

template<typename T>
inline bool balanced(BinNodePosi(T) x)    // 理想平衡
{   return get_height(x->rchild) == get_height(x->lchild);  }

template<typename T>
inline int balanced_factor(BinNodePosi(T) x)
{   return (get_height(x->rchild) - get_height(x->lchild));   }

template<typename T>
inline bool avl_balanced(BinNodePosi(T) x)
{   return ((-2 < balanced_factor(x)) && (balanced_factor(x) < 2));   }

template<typename T>
class AVL : public BST<T>
{
public:
    BinNodePosi(T) insert(const T&);
    bool remove(const T&);
};

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T& e)
{
    BinNodePosi(T)& x = this->search(e);
    if(x)   return x;
    x = new BinNode<T>(e, this->_hot);
    BinNodePosi(T) xx = x;
    this->_size++;
    for(BinNodePosi(T) g = x->parent; g; g = g->parent)
    {
        if(!avl_balanced(g))    // 如果不平衡
        {
            from_parent_to(x) = this->rotateAt(taller_child(taller_child(g)));
            break;
        }
        else    // 如果平衡
            this->update_height(x);    // 更新当前节点的高度
    }
    return xx;
}

template<typename T>
bool AVL<T>::remove(const T& e)
{
    BinNodePosi(T)& x = this->search(e);
    if(!x)  return false;
    removeAt(x, this->_hot);
    this->_size--;
    for(BinNodePosi(T) g = this->_hot; g; g = g->parent)
    {
        if(!avl_balanced(x))
            from_parent_to(g) = this->rotateAt(taller_child(taller_child(g)));
        this->update_height(g);   // 所有的祖先节点都要更新高度
    }
    return true;
}

#endif