#include"bst.hpp"
#include<algorithm>

template<typename T>
class redblack : public BST<T>
{
public:
    BinNodePosi(T) insert(const T& e);
    bool    remove(const T& e);
protected:
    void double_red(BinNodePosi(T) x);
    void double_blk(BinNodePosi(T) x);
    int update_height(BinNodePosi(T) x);
};

template<typename T>
inline bool is_black(BinNodePosi(T) x)
{   return !x || x->color == RB_BLACK;  }

template<typename T>
inline bool is_red(BinNodePosi(T) x)
{   return !is_black(x);  }

template<typename T>
int redblack<T>::update_height(BinNodePosi(T) x)
{
    x->height = std::max(get_height(x->lchild), get_height(x->rchild));
    if(is_black(x)) x->height++;
    return x->height;
}

template<typename T>
BinNodePosi(T) redblack<T>::insert(const T& e)
{
    BinNodePosi(T) x = search(e);
    if(x)   return x;
    x = new BinNode<T>(e, _hot, NULL, NULL, -1);
    double_red(x);
    return x ? x : _hot->parent;
}

template<typename T>
bool redblack<T>::remove(const T& e)
{
    BinNodePosi(T)& x = search(e);
    RBColor c = x->color;
    if(!x)  return false;
    BinNodePosi(T) r = removeAt(x, this->_hot);
    if(!(--(this->_size)))  return true;    // 只有一个节点
    if(!_hot)   // 删除的是根节点
    {
        _root->color = RB_BLACK;
        update_height(_root);
        return true;
    }
    if(c == RB_RED)  return true;   // 被删除的节点是红色，删除无影响
    if(is_red(r))   // r 是红色，改变为黑色，并更新黑高度
    {
        r->color = RB_BLACK;
        r->height++;
        return true;
    }
    double_blk(r);
    return true;
}

template<typename T>
void redblack<T>::double_red(BinNodePosi(T) x)
{
    BinNodePosi(T) p = x->parent;
    if(p->color != RB_RED)  return;
    BinNodePosi(T) g = p->parent;
    BinNodePosi(T) u = is_lchild(p) ? g->rchild : g->lchild;
    if(is_black(u))
    {
        BinNodePosi(T) gg = g->parent;
        BinNodePosi(T) r = rotateAt(x);
        r->color = RB_BLACK;
        r->lchild->color = RB_RED;
        r->rchild->color = RB_RED;
        from_parent_to(g) = r;
        r->parent = gg;
    }
    else
    {
        p->color = RB_BLACK;
        u->color = RB_BLACK;
        p->height++;    // 高度是等于黑节点的数量
        u->height++;
        if(!is_root(g)) g->color = RB_RED;
        double_red(g);
    }
}

template<typename T>
void redblack<T>::double_blk(BinNodePosi(T) x)
{
    BinNodePosi(T) p = x ? x->parent : this->_hot;  // 取父节点
    if(!p)  return;
    BinNodePosi(T) s = is_lchild(x) ? p->rchild : p->lchild;    //  取 x 的兄弟
    if(is_black(s))
    {
        // 取 s 的红孩子，如果都是，取左孩子
        BinNodePosi(T) t = NULL;
        if(is_red(s->rchild))   t = s->rchild;
        if(is_red(s->lchild))   t = s->lchild;
        if(t)   // NULL 会被视为黑色
        {
            RBColor pc = p->color;
            BinNodePosi(T) b = from_parent_to(p) = rotateAt(t);
            if(has_rchild(b))
            {
                b->rchild->color = RB_BLACK;
                update_height(b->rchild);
            }
            if(has_lchild(b))
            {
                b->lchild->color = RB_BLACK;
                update_height(b->lchild);
            }
            b->color = pc;
            update_height(b);
        }
        else    // s 没有红孩子
        {
            s->color = RB_RED;
            s->height--;
            if(is_red(p))
                p->color = RB_BLACK;
            else
            {
                p->height--;
                double_blk(p);
            }
        }
    }
    else    // s 为红色
    {
        s->color = RB_BLACK;
        p->color = RB_RED;
        BinNodePosi(T) t = is_lchild(s) ? s->lchild : s->rchild;
        _hot = p;
        from_parent_to(p) = rotateAt(t);
        double_blk(x);
    }
}