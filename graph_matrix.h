#ifndef _GRAPH_MATRIX_H_
#define _GRAPH_MATRIX_H_

#include<limits.h>
#include"graph.h"

template<typename Tv> struct Vertex   // 顶点
{
    Tv data;    // 数据
    int in_degree, out_degree; // 出入度数
    vstatus status; // 状态
    int dtime, ftime; //记录定点被发现和访问完的时刻
    int parent; // 父节点数量
    int priority;   // 在遍历树中的优先级
    Vertex(const Tv& d = (Tv)0)
    : data(d), in_degree(0), out_degree(0),\
      status(UNDISCOVERED), dtime(-1), ftime(-1),\
      parent(-1), priority(INT_MAX) {}
};

template<typename Te> struct Edge
{
    Te data;
    int weight; // 权重
    etype type; // 状态

    Edge(const Te& d, int w)
    : data(d), weight(w), type(UNDETERMINED)
    {}
};

template<typename Tv, typename Te>
class graph_matrix : public graph<Tv, Te>
{
private:
    vec<Vertex<Tv> > V;
    vec<vec<Edge<Te>*> >   E;

public:
    int e, n;
    graph_matrix()
    : n(0), e(0)
    {}

    ~graph_matrix()
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                delete E[i][j];
    }
    
    Tv& vertex(int i) const
    {   return V[i].data;   }

    int inDegree(int i) const
    {   return V[i].in_degree;  }

    int outDegree(int i) const
    {   return V[i].out_degree; }

    int& fTime(int i) const
    {   return V[i].ftime;  }

    int& dTime(int i) const
    {   return V[i].dtime;  }

    int& parent(int i) const
    {   return V[i].parent;  }

    int& priority(int i) const
    {   return V[i].priority;  }

    vstatus& status(int i) const
    {   return V[i].status;  }

    bool exists(int i, int j) const
    {
        return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j];
    }

    etype& type(int i, int j) const
    {   return E[i][j]->type;   }

    int& weight(int i, int j) const
    {   return E[i][j]->weight; }

    Te& edge(int i, int j) const
    {   return E[i][j]->data;   }

    void insert(int i, int j, const Te& d, int w)
    {
        // 如果边已存在，直接返回
        if(exists(i, j))    return;
        E[i][j] = new Edge<Te>(d, w);
        V[i].out_degree++;
        V[j].in_degree++;
        e++;
    }

    Te remove(int i, int j)
    {
        Te eBak = edge(i, j);
        V[i].out_degree--;
        V[i].in_degree--;
        delete E[i][j];
        E[i][j] = NULL;
        e--;
        return eBak;
    }

    int insert(const Tv& v)
    {
        for(int i = 0; i < n; i++)
            E[i].insert(NULL);
        n++;
        E.insert(vec<Edge<Te>*>(n, n, (Edge<Te>*)NULL)); // 添加一个容量，长度为n，初值为NULL 的边记录
        return V.insert(vertex(v));
    }

    Tv remove(int i)
    {
        // 删除 i 的出边
        for(int j = 0; j < n; j++)
        {
            // 如果存在边(i, j)，移除边，和j 的入度
            if(exists(i, j))
            {
                delete E[i][j];   // 删除 [i][j] 指向的内存，表中的 i 行仍存在
                V[j].in_degree--;
            }
        }
        E.remove(i);
        n--;
        // 删除 i 的入边
        for(int j = 0; j < n; j++)
        {
            if(exists(j, i))
            {
                delete E[j][i];
                V[j].out_degree--;
            }
        }
        Tv vBak = vertex(i);
        V.remove(i);
        return vBak;
    }
};

#endif
