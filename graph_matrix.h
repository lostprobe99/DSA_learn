#ifndef _GRAPH_MATRIX_H_
#define _GRAPH_MATRIX_H_

#include<limits.h>
#include"graph.h"
#include"vec.hpp"

template<typename Tv>
struct vertex   // 定点
{
    Tv data;    // 数据
    int in_degree, out_degree; // 出入度数
    vstatus status; // 状态
    int dtime, ftime; //记录定点被发现和访问完的时刻
    int parent; // 父节点
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
    graph_matrix();
    ~graph_matrix();
};

template<typename Tv, typename Te>
inline void graph_matrix<Tv, Te>::insert(int i, int j, const Te& edge, int weight)
{
    E[i][j] = new edge(edge, weight);
    V[i].out_degree++;
    V[j].in_degree++;
}

#endif
