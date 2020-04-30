#include"bst.hpp"

template<typename T>
class Splay : public BST<T>
{
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v);
public:
    BinNodePosi(T)& search(const T& e)
    {
        BinNodePosi(T)& x = searchIn(this->_root, e, this->_hot = NULL);
        this->_root = splay(x ? x : this->_hot);    // 如果未找到元素，将其父节点移至根
        return this->_root;
    }
    BinNodePosi(T)  insert(const T& e)
    {
        if(!this->_root)  // 原树为空
        {
            this->_size++;
            return this->_root = new BinNode<T>(e);
        }
        // 该元素已存在
        if(e == search(e)->data)    return this->_root;
        // 上一句中已经执行过一次 search 也即执行过一次 splay
        BinNodePosi(T) t = this->_root;
        this->_size++;
        if(t->data < e){
            this->_root->parent = this->_root = new BinNode<T>(e, NULL, t, t->rchild);
            if(has_rchild(t)){
                t->rchild->parent = this->_root;
                t->rchild = NULL;
            }
        } else {
            this->_root->parent = this->_root = new BinNode<T>(e, NULL, t->lchild, t);
            if(has_lchild(t)){
                t->lchild->parent = this->_root;
                t->lchild = NULL;
            }
        }
        this->update_height_above(t);
        return this->_root;
    }
    bool remove(const T& e)
    {
        if(!this->_root || e != search(e)->data) return false;
        BinNodePosi(T) x = this->_root;
        if(!has_lchild(x)){
            this->_root = this->_root->rchild;
            if(this->_root)   this->_root->parent = NULL;
        } else if (!has_rchild(x)){
            this->_root = this->_root->lchild;
            if(this->_root)   this->_root->parent = NULL;
        } else {
            BinNodePosi(T) lt = this->_root->lchild;
            this->_root->lchild = NULL;   lt->parent = NULL;
            this->_root = this->_root->rchild;  this->_root->parent = NULL;
            search(x->data);    // 将右子树中最小的节点伸展到树根
            this->_root->lchild = lt; lt->parent = this->_root; // 接回原左子树
        }
        delete x;
        this->_size--;
        if(this->_root)   this->update_height(this->_root);
        return true;
    }
};

template<typename T> inline
void attachAsRC(BinNodePosi(T) p, BinNodePosi(T) r)
{
    p->rchild = r;
    if(r)   r->parent = p;
}

template<typename T> inline
void attachAsLC(BinNodePosi(T) p, BinNodePosi(T) l)
{
    p->lchild = l;
    if(l)   l->parent = p;
}

template<typename T>
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v)
{
    if(!v)  return NULL;
    BinNodePosi(T) p; BinNodePosi(T) g;
    while((p = v->parent) && (g = v->parent))   // v 的祖先>=3层
    {
        BinNodePosi(T) gg = g->parent;
        // 对局部进行旋转
        if(is_lchild(v)) {
            if(is_lchild(p)) {   // 左左
                attachAsLC(g, p->rchild);
                attachAsRC(p, g);
                attachAsLC(p, v->rchild);
                attachAsRC(v, p);
            } else {   // p 在右，v 在左
                attachAsLC(p, v->rchild);
                attachAsRC(g, v->lchild);
                attachAsLC(v, g);
                attachAsRC(v, p);
            }
        } else{
            if(is_rchild(p)) {   // 右右
                attachAsRC(g, p->lchild);
                attachAsLC(p, g);
                attachAsRC(p, v->lchild);
                attachAsLC(v, p);
            } else {   // p 左，v 右
                attachAsRC(p, v->lchild);
                attachAsLC(g, v->rchild);
                attachAsLC(v, p);
                attachAsRC(v, g);
            }
        }
        // 旋转完成后，将局部根节点接到原树
        if(!gg) v->parent = NULL;
        // 判断原来的 g 节点是左孩子还是右孩子，依此将 v 接入
        else    (g == gg->lchild ? attachAsLC(gg, v) : attachAsRC(gg, v));
        // 更新高度
        this->update_height(g);
        this->update_height(p);
        this->update_height(v);
    }
    if(p = v->parent)   // v 只有一层祖先
    {
        if(is_lchild(v)) {
            attachAsLC(p, v->rchild);
            attachAsRC(v, p);
        } else {
            attachAsRC(p, v->lchild);
            attachAsLC(v, p);
        }
        this->update_height(p);
        this->update_height(v);
    }
    v->parent = NULL;   // 调整后，v 成为根节点
    return v;
}