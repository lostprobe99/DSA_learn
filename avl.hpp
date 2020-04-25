#ifndef _AVL_HPP_
#define _AVL_HPP_

#include"bst.hpp"

template<typename T>
inline bnodePosi(T)& taller_child(const bnodePosi(T)& x)
{
    if(get_height(x->lchild) > get_height(x->rchild))
        return x->lchild;
    else if(get_height(x->lchild) < get_height(x->rchild))
        return x->rchild;
    else
        return is_lchild(x) ? x->lchild : x->rchild;
}

template<typename T>
inline bool balanced(bnodePosi(T) x)    // 理想平衡
{   return get_height(x->rchild) == get_height(x->lchild);  }

template<typename T>
inline int balanced_factor(bnodePosi(T) x)
{   return (get_height(x->rchild) - get_height(x->lchild));   }

template<typename T>
inline bool avl_balanced(bnodePosi(T) x)
{   return (-2 < balanced_factor(x)) && (balanced_factor(x) < 2);   }

template<typename T>
static inline bnodePosi(T) rotateAt(bnodePosi(T) v)
{
    bnodePosi(T) p = v->parent; g = p->parent;
    if(is_lchild(p))
    {
        if(is_lchild(v)){
            p->parent = g->parent;  // 确立变换后的局部根节点
            this->connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
        }
        else{
            v->parent = g->parent;
            this->connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
        }
    }
    else
    {
        if(is_rchild(v)){
            p->parent = g->parent;
            this->connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
        }
        else{
            v->parent = g->parent;
            this->connect34(g, v, g, g->lchild, v->lchild, v->rchild, p->rchild);
        }
    }
}

template<typename T>
class AVL : public BST<T>
{
public:
    bnodePosi(T) insert(const T&);
    bool remove(const T&);
};

template<typename T>
bnodePosi(T) AVL<T>::insert(const T& e)
{
    bnodePosi(T)& x = search(e);
    if(x)   return x;
    x = new bnode<T>(e, this->_hot);
    this->_size++;
    for(bnodePosi(T) g = x->parent; g; g = g->parent)
    {
        if(!avl_balanced(g))    // 如果不平衡
        {
            from_parent_to(x) = rotateAt(taller_child(taller_child(g)));
            break;
        }
        else    // 如果平衡
            this->update_height(x);    // 更新当前节点的高度
    }
}

template<typename T>
bool AVL<T>::remove(const T& e)
{
    bnodePosi(x)& = search(e);
    if(!x)  return false;
    removeAt(x, _hot);
    _size--;
    for(bnodePosi(T) g = _hot; g; g = g->parent)
    {
        if(!avl_balanced(x))
            from_parent_to(g) = rotateAt(taller_child(taller_child(g)));
        update_height(g);   // 所有的祖先节点都要更新高度
    }
}

#endif