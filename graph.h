#ifndef _GRAPH_H_
#define _GRAPH_H_

#include"stack.hpp"
#include<limits.h>

typedef enum {
    UNDISCOVERED,
    DISCOVERED,
    VISITED
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
    void BFS(int, int&);
    void DFS(int, int&);
    void BCC(int, int&, stack<Tv>&);
    bool TSort(int, int&, stack<Tv>*);
    template<typename PU> void PFS(int, PU);

public:
    int n; // 点和点操作
    virtual int      insert (const Tv& ) = 0;
    virtual Tv       remove (int) = 0;
    virtual Tv&      vertex(int) = 0;
    virtual int      inDegree(int) = 0;
    virtual int      outDegree(int) = 0;
    virtual int&     fTime(int) = 0;
    virtual int&     dTime(int) = 0;
    virtual int&     parent(int) = 0;
    virtual int&     priority(int) = 0;
    virtual vstatus& status(int) = 0;

    int e;  // 边和边操作
    virtual bool     exists(int, int) = 0;
    virtual etype&   type(int, int) = 0;
    virtual int&     weight(int, int) = 0;
    virtual Te&      edge(int, int) = 0;
    virtual void     insert(int, int) = 0;
    virtual Te       remove(int, int) = 0;
};

#endif
