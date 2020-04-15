## tree

### 二叉树（binay tree）

#### 节点类设计

```c++
template<typename T>
struct bnode
{
    T data;
    bnode<T> *parent, *lchild, *rchild;
    int height;

    bnode()
    : parent(NULL), lchild(NULL), rchild(NULL), height(0)
    {}

    bnode(const T& e, bnode<T>* p = NULL, bnode<T> *lc = NULL,bnode<T> *r = NULL, int h = 1)
    : data(e), parent(p), lchild(lc), rchild(rc), height(h)
    {}

    int size() const; // 返回当前节点以及所有后代的数量
    bnode<T>* insertAsLC(const T& e);   // 作为左节点插入
    bnode<T>* insertAsRC(const T& e);   // 作为右节点插入
}
```

#### 树类

```c++
template<typename T>
class btree
{
private:
    int _size;
    bnode<T>* _root;
    virtual int update_height(bnode<T>* x); // 更新高度
    int update_height_above(bnode<T>* x);   // 更新祖先高度
public:
    btree() : _size(0), _root(NULL);
    ~btree();
    int size() const;   // 返回树的规模
    int remove(bnode<T> * x); // 移除一棵子树
    bool empty();   // 判空
    bnode<T>* root() const; // 访问根
    bnode<T>* isnertAsRoot(const T& e); // 作为根插入
    bnode<T>* isnertAsRc(const T& e); // 作为右孩子插入
    bnode<T>* isnertAsLc(const T& e); // 作为左孩子插入
    template<typename VST>
    void trav_pre(bnode<T>* x, VST& visit); // 从x开始先序遍历
    void trav_pre_loop(bnode<T>* x, VST& visit); // 以迭代方式进行先序遍历
}
```

#### 先序遍历（迭代 I）

```c++
template <typename T> template <typename VST>
void btree<T>::trav_pre_loop_I(bnode<T>* x, VST& visit)
{
    stack<bnode<T *> > s;
    s.push(x);
    while(!s.empty())
    {
        x = s.pop();
        visit(x->data);
        if(x->rchild)
            s.push(x->rchild);
        if(x->lchild)
            s.push(x->lchild);
    }
}
```

借助于栈实现。初始时把节点`x`入栈。从栈中弹出一个节点赋值给`x`并访问，然后依次把`x`的右子节点入栈，左子节点入栈，循环执行，至栈空。

由于栈的先进后出的特点，后入栈的左子节点先被访问，然后将`x`的右子节点和左子节点依次入栈，然后访问`x`的左子节点的左子节点，如此循环。

#### 先序遍历（迭代 II）

```c++
template<typename T> template<typename VST>
void btree<T>::trav_pre_loop_II(bnode<T>* x, VST& visit)
{
    stack<bnode<T>*> s;
    while(true)
    {
        // 访问x的左支
        while(x)
        {
            visit(x->data);
            s.push(x->rchild);
            x = x->lchild;
        }
        if(s.empty())
            break;
        x = s.pop();
    }
}
```

访问`x`的左支，并将`x`的右子节点入栈缓存，`x`的左分支访问完成后，将`x`的右子节点弹出，设为`x`，循环进行以上步骤。

#### 中序遍历（迭代）

```c++
template<typename T> template<typename VST>
void btree<T>::trav_in_loop_I(bnode<T>* x, VST& visit)
{
    stack<bnode<T>*> s;
    while(true)
    {
        while(x)
        {
            s.push(x);
            x = x->lchild;
        }

        if(s.empty())   break;
        x = s.pop();
        visit(x->data);
        x = x->rchild;
    }
}
```

时间复杂度：$O(n)$ 因为无论是内循环还是外循环，每个节点都只访问了一次。

进入`x`左支的底部，用一个栈保存沿途遇到的节点，然后从栈中取出一个节点访问，然后转向这个节点的右子节点，因为在内循环中对节点有效性做了判断，所以`x = x->rchild`前无需进行判断，否则`x`不会继续推进。