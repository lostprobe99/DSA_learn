#include"bst.hpp"
#include<algorithm>

template<typename T>
inline bool is_black(BinNodePosi(T) x)
{   return !x || x->color == RB_BLACK;  }

template<typename T>
inline bool is_red(BinNodePosi(T) x)
{   return !is_black(x);  }

template<typename T>
class redblack : public BST<T>
{
protected:
    BinNodePosi(T) insert(const T& e);
    bool    remove(const T& e);
public:
    void double_red(BinNodePosi(T) x);
    void double_blk(BinNodePosi(T) x);
    int update_height(BinNodePosi(T) x);
};

template<typename T>
int redblack<T>::update_height(BinNodePosi(T) x)
{
    x->height = std::max(get_height(x->lchild), get_height(x->rchild));
    if(is_black(x)) x->height++;
    return x->height;
}

template<typename T>
BinNodePosi(T) insert(const T& e)
{
    BinNodePosi(T) x = search(e);
    if(x)   return x;
    x = new BinNode<T>(e, _hot, NULL, NULL, -1);
    double_red(x);
    return x ? x : _hot->parent;
}