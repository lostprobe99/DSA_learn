#include"../vec.hpp"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

void test_vec();

class print{
public:
    print(){}
    void operator()(int & e)
    {   printf("%d ", e);   }
};
class sum{
public:
    int _sum;
    sum() : _sum(0) {}
    void operator()(int & e)
    {   _sum += e;   }
};

void test_vec()
{
    cout << "-----vector-----" << endl;    
    #define FUNC_TEST(info, x, y)   printf(info, (x), (y))
    #define REMOVED(x, y) FUNC_TEST("remove %d by %d\n", (x), (y))
    #define FIND(x, y)    FUNC_TEST("find %d at %d\n", (x), (y))

    print p;
    int nums[] = {19, 117, 124, 124, 308, 539, 773, 819, 847, 936};
    const vec<int> v2(nums, 0, 10);
    vec<int> v1(v2, 0, 10);

    v1.traverse(p);
    cout << endl;

    int r1 = v1.search(117, 0, v1.size());
    cout << r1 << " " << v1.get(r1) << endl;
    cout << r1 + 1 << " " << v1.get(r1 + 1) << endl;
    v1.swap(0, v1.size() - 1);

    cout << "before sort: " << endl;
    v1.traverse(p);
    cout << endl;
    
    cout << "after sort: " << endl;
    v1.sort(0, v1.size());
    v1.traverse(p);
    cout << endl;
    
    sum s;
    v1.traverse(s);
    cout << "sum of v1: "<< s._sum << endl;

    cout << "use operator[] read " << endl;
    for(int i = 0; i < v1.size(); i++)
        cout << v1[i] << " ";

    cout << endl;
    cout << "use operator[] modify " << endl;
    for(int i = 0; i < v1.size(); i++)
    {
        cout << (v1[i] = i) << " ";
    }
}
