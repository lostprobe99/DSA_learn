#ifndef _GRAPH_H_
#define _GRAPH_H_

#include"stack.hpp"
#include<limits.h>
#include"queue.hpp"

typedef enum {
    UNDISCOVERED,   // 表示未被发现
    DISCOVERED,     // 正在访问
    VISITED         // 访问完成
} vstatus;

typedef enum{
    UNDETERMINED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD,
} etype;

template<typename Tv, typename Te>
class graph
{
private:
    void reset()
    {
        // 点信息复位
        for(int i = 0; i < n; i++)
        {
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1;
            parent(i) = -1;
            priority(i) = INT_MAX;

            for(int j = 0; j < e; j++)
                if(exists(i, j))    type(i, j) = UNDETERMINED;
        }
    }
    void BFS(int v, int& clock)
    {
        queue<int> q;
        q.enqueue(v);
        status(v) = DISCOVERED;
        while(!q.empty())
        {
            v = q.dequeue();
            dTime(v) = ++clock;
            for(int u = firstNbr(v), -1 < u; u = nextNbr(v, u))
            {
                if(status(u) == UNDISCOVERED)
                {
                    status(u) = DISCOVERED; // 如果定点 u 未被发现，入队
                    q.enqueue(u);
                    type(v, u) = TREE;  // 设置边的状态为 TREE 代表这条边被采纳
                    parent(u) = v;  // 把 v 作为 u 的父节点
                }
                else    // 如果 u 在队列中(DISCOVERED)或已出队(VISITED)
                    type(u, v) = CROSS;
            }
            status(v) = VISITED;    // 当 v 的所有邻边和相邻节点访问完成后，标记 v 为已访问
        }
    }
    void DFS(int, int&);
    void BCC(int, int&, stack<Tv>&);
    bool TSort(int, int&, stack<Tv>*);
    template<typename PU> void PFS(int, PU);

public:
    int n; // 点和点操作
    virtual int      insert (const Tv& ) = 0;
    virtual Tv       remove (int) = 0;
    virtual Tv&      vertex(int) const = 0;
    virtual int      inDegree(int) const = 0;
    virtual int      outDegree(int) const = 0;
    virtual int&     fTime(int) const = 0;
    virtual int&     dTime(int) const = 0;
    virtual int&     parent(int) const = 0;
    virtual int&     priority(int) const = 0;
    virtual vstatus& status(int) const = 0;
    virtual int firstNbr(int) = 0;
    virtual int nextNbr(int, int) = 0;

    int e;  // 边和边操作
    virtual bool     exists(int, int) const = 0;
    virtual etype&   type(int, int) const = 0;
    virtual int&     weight(int, int) const = 0;
    virtual Te&      edge(int, int) const = 0;
    virtual void     insert(int, int, const Te&, int) = 0;
    virtual Te       remove(int, int) = 0;

    void bfs(int s)
    {
        // 初始化
        reset();
        int clock = 0;
        int v = s;

        do{
            if(status(v) == UNDISCOVERED)
                BFS(v, clock);
            v = (++v) % n;
        }while(s != v)
    }
    void dfs(int);
    void bcc(int);
    stack<Tv*> tSort(int);
    void prim(int);
    void dijkstra(int);
    template<typename PU> void pfs(int, PU);
};

#endif
