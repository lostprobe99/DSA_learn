## vector

### 头文件防卫

`#praga once`      编译相关

`#ifndef/#define/#endif`  语言相关

要确保通用性时需要使用宏

### 模板类的分离式编译
&emsp;&emsp;调用模板类时，需要包含对应的`.cpp/hpp `文件，否则会发生链接错误，因为template<...>在编译时不会被分配空间，它一直处于等待状态，直到获得第一个模板的实例

When call a template class, you need include relevant `cpp/hpp` files,otherwise occur link errors. Because the template<...> is not allocated when compiled, It waits until it gets the first template instance.

&emsp;&emsp;c++标准提到，一个编译单元指一个`.cpp` 文件和它所包含的所有`.h`文件，.h文件中的代码会扩展到包含它的`cpp` 文件中，然后被编译为一个`obj`文件，`obj`文件拥有可执行性，而且它包含的就是二进制码，但未必能执行，因为其中未必会有main函数。当编译器把所有文件编译完成后，链接器会将其连接为一个`exe`文件。

&emsp;&emsp;在编译时，如果编译器未找到相关函数的实现，就会认为它的代码在其他的`obj`中，编译时会在调用处生成一条call指令，而这个指令显然是错误的，因为在上下文中没有关于这个函数的实现，而链接器在其他`obj`中寻找函数的实现代码，找到后将这个call的地址替换为函数的实际地址。

&emsp;&emsp;模板不会编译为二进制代码，其中需要一个"具现"的过程。当模板的声明和实现分离时，如果只包含相关模板的.h文件，编译器会寻找关于这个实例的代码，然而上下文中并没有相关代码，因为标准规定当一个模板未被用到时，就不应该具现它。然后，链接器在其他`obj`文件中寻找，而显然，`obj`文件中不会有关于这个实例的代码，于是报连接错误。

&emsp;&emsp;在编译一个`cpp`文件时编译器不知道另一个`cpp`文件的存在，也不会去查找，遇到未决符号时就会把问题传给链接器。而模板在需要的时候才会具现，所以如果编译器只看到模板的声明，它就无法具现模板，只能作出标记，希望链接器能够找到实际地址。在编译实现模板的`cpp`文件时，由于文件中不存在模板的实现，所以编译器也不会去具现，所以整个工程中就找不到模板的实例的代码，于是链接器报错。

## vec

### uniquify
```c++
template <typename T>
int vec<T>::uniquify()
{
    int old_size = _size;
    for(int i = 1; i < _size; i++)
        find(_elem[i], 0, i) < 0 ? i++ : remove(i);
    return old_size - _size;
}
```
时间复杂度：$O(n^2)$

每次循环，`find` 在 $\_elem[0...i)$ 中查找 $\_elem[i]$ 是否存在，如果存在则调用 `remove​` 函数将其移除，​`remove` 通过把 $\_elem(i+1...n)$ 整体前移一位实现删除 $\_elem[i]$ 并且内部会将 $\_size$ 减一。

Each loop, `find` function find $\_elem[i]$ in $\_elem[0...i)$. If it exist, call the `remove` function remove it. `remove` by make $\_elem(i...n)$ forward one come true delete $\_elem[i]$ and inside make $\_size$ minus one.

所以 `find​` 和 `remove` 各自的复杂度不超过 $n$ ，所以每次循环消耗的时间不超过 $n$ ，循环 $n$ 次共需要 $n^2$ 的时间。

### traverse
```c++
// vec.hpp
template<typename T>
template<typename VST>
void vec<T>::traverse(VST & visit)
{
    for(int i = 0; i < _size; i++)
        visit(_elem[i]);
}
```
```c++
// main.cpp
struct print{
    void operator()(int & e)
    {   printf("%d ", e);   }
}

int nums[0, 1, 2, 3, 4, 5, 6, 7];
vec<int> v1(nums, 0, 8);
print p;
v1.traverse(p);
```
&emsp;&emsp;本例中，`p`是一个函数对象，调用它的语句在 `vec<T>::traverse` 的函数体中：`visit(...)`，实际上这是调用了print类中重载的运算符`()`，而实际使用过程中看起来像是调用一个函数，因此称为函数对象。

For this example, the `p` is a function object, it is called in function `vec<T>::traverse` body, that is `visit(...)`. In fact, This is call the overloading operator `()` , but it is used like call a function, so name function object.

&emsp;&emsp;给`v.traverse`传入的参数是一个对象，`v.traverse`内部会调用该对象的`()`运算符。

The parameter `p` was passed to `v.traverse` that is a object, `v.traverse` will call the `()` by the object.

&emsp;&emsp;如果写成 `v.traverse(p())` ，语法上会出错，因为在本例中 `p.()` 是没有返回值的，`p()` 不会产生一个值传递给 `v.traverse`。

### search

```c++
template<typename T>
int vec<T>::search(T e, int lo, int hi)
{
    int mi = 0;
    while(lo + 1 < hi)
    {
        mi = (lo + hi) >> 1;
        e < _elem[mi] ? hi = mi : lo = mi;
    }
    return lo;
}
```

时间复杂度：$O(\log(n))$ 每次循环后待查找数组剩下一半，长度为 $n$ 的数组需要 $x=\log_2^n$次循环

语义：`search(e, a, b)` ，在 $[a, b)$ 中查找不大于 $e$ 的最大元素，并返回该元素的索引。

例如数组 `nums = [19, 117, 124, 124, 308, 539, 773, 819, 847, 936]` ，`nums.search(124, 0, nums.size())` 操作返回`3`，`nums[3]=124, nums[4] = 308` ，所以`3`是一个符合语义的结果。

对于此数组，第一次循环后`nums = nums[0 : 5]`，第二次循环后`nums = nums[2 : 5]`，第三次循环后`nums = nums[3 : 5]`，第四次循环后`nums = nums[3 : 4]`，此时`nums[lo] = 124 = e, nums[hi] = 308`，`lo`和`hi`之间没有其他元素，于是退出循环，返回当前的`lo`。

### sort

#### bubble sort

```c++
template <typename T>
void vec<T>::bubble(int lo, int hi)
{
    while(++lo, hi)
    {
        if(_elem[lo - 1] < _elem[lo])
            swap(lo - 1, lo);
	}
}
template <typename T>
void vec<T>::bubble_sort(int lo, int hi)
{
    while(lo < hi)
        bubble(lo, hi--);
}
```

时间复杂度：$O(n^2)$

每次将待排数组中的最大值移到数组最右端，使最右端部分有序，同时待排数组右边界减一，循环进行，知道待排数组为空。

由于该算法每次使待排数组长度减一，所以假如待排数组部分有序，对于有序的部分依然是每次循环长度减一，考虑加以改进，使其跳过有序部分。

改进：

```c++
template <typename T>
bool vec<T>::bubble(int lo, int hi)
{
    bool sorted = true;
    while(++lo < hi)
    {
        if(_elem[lo - 1] < _elem[lo])
        {
            sorted = false;
            swap(lo - 1, hi);
        }
    }
    return sorted;
}
template <typename T>
void vec<T>::bubble_sort(int lo, int hi)
{	while(!bubble(lo, hi--));	}
```

这一版本中，加入了一个指示是否有序的标志`sorted`。在待排数组中，如果未找到`A[lo - 1] > A[lo]`的情况，返回一个真值代表待排数组已有序。`while(!bubble(lo, hi--))`退出循环。

与上一版本相比，这个版本在处理有序或部分有序的数组时效率会更好一些。而如果数组右端多数元素有序，左端少数元素无序时，依然会花费大量的时间将右端逐一排除。

如果记录上一次循环中最后一次交换的元素的位置，作为下一次循环中的右边界，就相当于跳过了右端大部分有序的元素。

改进：

```c++
template <typename T>
int bubble(int lo, int hi)
{
    int last = lo;
	while(++lo < hi)
    {
        if(_elem[lo - 1] < _elem[hi])
        {
            swap(lo - 1, hi);
            last = lo;
        }
    }
    return lase;
}
template <typename T>
void bubble_sort(int lo, int hi)
{	while(lo < (hi = bubble(lo, hi)));	}
```

#### merge sort

```c++
template <typename T>
void merge(int lo, int mi, int hi)
{
    int lb = mi - lo, lc = hi - mi;
    T * A = _elem + lo;
    T * B = new T[lb], *C = _elem + mi;
    for(int i = 0; i < lb; i++)
        A[i] = B[i];
    for(int i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
    {
        if((j < lb) && (k >= lc || B[j] <= C[k]))    A[i++] = B[j++];
        if((k < lc) && (j >= lb || B[j] >  C[k]))    A[i++] = C[k++];
    }
    delete [] B;
}

template <typename T>
void merge_sort(int lo, int hi)
{
    if(lo + 1 < hi) return;
    int mi = (lo + hi) >> 1;
    merge_sort(lo, mi);
    merge_sort(mi, hi);
    merge(lo, mi, hi);
}
```
时间复杂度：$O(\log n)$
递归基：`if(lo + 1 < hi) return;`确保数组中只剩下一个元素时返回堆栈的上一层，在这一层中数组有两个元素，随后进入`merge`函数。
`merge`函数将两个有序数组 $\_elem[lo...mi]$ 和 $\_elem[mi...hi]$ 合并为一个有序数组。`merge` 会备份B段  $[lo...hi]$ 的元素，C段 $[mi...hi]$ 无需备份，因为可以确保任何时刻`j`不会超过`k`。两个判断中`k >= lc`和`j >= lb`确保两个子数组中如果有一个已清空，另一个中的元素能够直接连接到数组`A`上。