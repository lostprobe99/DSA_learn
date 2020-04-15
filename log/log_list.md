## list

### 节点类设计

```c++
#define posi(T) listnode<T>
template<typename T>struct listnode
{
    T data;
    posi(T) pred;
    posi(T) succ;
    listnode(){}
    listnode(T e, posi(T) pre = NULL, posi(T) nxt = NULL)
    : data(e), pred(pre), succ(nxt)
    {}
    posi(T) insert_as_pred(T const & e);
    posi(T) insert_as_after(T const & e);
};
```

### insert_as_pred

```c++
template <typename T>
posi(T) insert_as_pred(T const & e)
{
    // 以e为数据，当前节点的前驱为前驱，当前节点为后继 创建新节点
    posi(T) x = new listnode(e, this->pred, this);

    // 把当前节点的前驱的后继设为新节点
    this->pred->succ = x;

    // 把当前节点的前驱设为新节点
    this->pred = x;
    return x;
}
```

### 列表类设计
```c++
template <typename T> class list
{
private:
    int _size;
    posi(T) header;
    posi(T) tailer;
public:
    /* ... */
};
```
`header`是第一个节点前的哨兵节点，称为**头节点**，列表的第一个节点称为**首节点**
`tailer`是最后一个节点的后一个节点，称为**尾节点**，最后一个节点称为**末节点**

### find

```c++
template<typename T> posi(T) list<T>::find(T const & e, int n, posi(T) p) const;
template<typename T> posi(T) list<T>::find(T const & e, posi(T) p, int n) const;
```

`find`函数用于在p的前驱或后继中（并不包括p）查找`data`等于`e`的节点

两种写法的不同之处在于，n在p的前面代表在p的前驱中查找，在后面则表示在p的后继中查找

### insert before
```c++
template<typename T>
posi(T) list<T>::insert_before(posi(T) p, T const & e)
{
    _size++;
    return p->insert_as_pred(e);
}
```

### sort

#### selection sort

`selection_sort`用于对`p`到`p`的`n`个后继排序

```c++
template <typename T>
void selection_sort(posi(T) p, int n)
{
    // x，y 作为两侧的哨兵节点，不会被选取到
    // 找出待排序区间的首节点和末节点
    posi(T) x = p->pred;
    posi(T) y = p;
    for(int i = 0; i < n; i++)
        y = y->succ;

    while(1 < n)
    {
        insert_before(y, remove(select_max(x, n)));
        y = y->pred;
        n--;
    }
}
```
由于`new`和`delete`操作消耗的时间是其他基本操作的大约100倍，所以也可以只更改`data`区，不操作节点
```c++
template <typename T>
void selection_sort(posi(T) p, int n)
{
    posi(T) x = p;  // 这种方法不改变节点，所以直接把p作为左闭边界
    posi(T) y = p;
    for(int i = 0; i < n; i++)
        y = y->succ;

    while(1 < n)
    {
        // 交换数据域，不再改变节点
        swap(y->pred->data, select_max(x, n)->data);
        y = y->pred;
        n--;
    }
}
```

#### insertion sort

```c++
template <typename T>
posi(T) list<T>::search(T const & e, int n, posi(T) p) const
{
    while(0 <= n--)
        if((p = p->pred)->data <= e)
            break;
    return p;
}

template <typename T>
void list<T>::insertion_sort(posi(T) p, int n)
{
    for(int i = 0; i < n; i++)
    {
        insert_after(search(p->data, i), p->data);
        p = p->succ;
        remove(p->pred);
    }
}
```

时间复杂度：$O(n)$

语义和`selection_sort`相同

`search` 用于在 `p` 的 `n` 个前驱中找到不大于 `e` 的最大值

`insertion_sort` 把列表分为两部分，并认为左侧有序，右侧无序。有序部分从0开始，每次选择右侧右边界上的节点，在左侧的有序区段找到一个不大于其值的最大节点，把当前值作为一个新节点插入到目标节点后，同时有序区段长度加一。并删除原本所在的节点