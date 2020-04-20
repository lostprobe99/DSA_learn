#ifndef _GRAPH_MATRIX_H_
#define _GRAPH_MATRIX_H_

#include<limits.h>
#include"graph.h"

template<typename Tv>
struct vertex   // 顶点
{
    Tv data;    // 数据
    int in_degree, out_degree; // 出入度数
    vstatus status; // 状态
    int dtime, ftime; //记录定点被发现和访问完的时刻
    int parent; // 父节点数量
    int priority;   // 在遍历树中的优先级
    vertex(const Tv& d)
    : data(d), in_degree(0), out_degree(0),\
      status(UNDISCOVERED), dtime(-1), ftime(-1),\
      parent(-1), priority(INT_MAX) {}
};

template<typename Te>
struct edge
{
    Te data;
    int weight; // 权重
    etype type; // 状态

    edge(const Te& d, int w)
    : data(d), weight(w), type(UNDETERMINED)
    {}
};

template<typename Tv, typename Te>
class graph_matrix : public graph<Tv, Te>
{
private:
    vec<vertex<Tv> > V;
    vec<vec<edge<Te>*> >   E;

public:
    graph_matrix()
    {   n = 0;  e = 0;  }

    ~graph_matrix()
    {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            delete E[i][j];
    }

    int n;
    int      insert (const Tv& );
    Tv       remove (int);
    Tv&      vertex(int) const;
    int      inDegree(int) const;
    int      outDegree(int) const;
    int&     fTime(int) const;
    int&     dTime(int) const;
    int&     parent(int) const;
    int&     priority(int) const;
    vstatus& status(int) const;

    int e;
    bool     exists(int, int) const;
    etype&   type(int, int) const;
    int&     weight(int, int) const;
    Te&      edge(int, int) const;
    void     insert(int, int, const Te&, int);
    Te       remove(int, int);
};

#endif
