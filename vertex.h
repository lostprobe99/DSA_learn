#ifndef _VERTEX_H_
#define _VERTEX_H_

#include<limits.h>

typedef enum{
    UNDISCOVERED,
    DISCOVERED,
    VISITED
}   vstatus;

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

#endif
