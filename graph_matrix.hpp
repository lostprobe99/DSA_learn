#include"graph_matrix.h"

template<typename Tv, typename Te>
inline Tv& graph_matrix<Tv, Te>::vertex(int i) const
{   return V[i].data;   }

template<typename Tv, typename Te>
inline int graph_matrix<Tv, Te>::inDegree(int i) const
{   return V[i].in_degree;  }

template<typename Tv, typename Te>
inline int graph_matrix<Tv, Te>::outDegree(int i) const
{   return V[i].out_degree; }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::fTime(int i) const
{   return V[i].ftime;  }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::dTime(int i) const
{   return V[i].dtime;  }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::parent(int i) const
{   return V[i].parent;  }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::priority(int i) const
{   return V[i].priority;  }

template<typename Tv, typename Te>
inline vstatus& graph_matrix<Tv, Te>::status(int i) const
{   return V[i].status;  }

template<typename Tv, typename Te>
inline bool graph_matrix<Tv, Te>::exists(int i, int j) const
{
    return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j];
}

template<typename Tv, typename Te>
inline etype& graph_matrix<Tv, Te>::type(int i, int j) const
{   return E[i][j]->type;   }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::weight(int i, int j) const
{   return E[i][j]->weight; }

template<typename Tv, typename Te>
inline Te& graph_matrix<Tv, Te>::edge(int i, int j) const
{   return E[i][j]->data;   }

template<typename Tv, typename Te>
inline void graph_matrix<Tv, Te>::insert(int i, int j, const Te& edge, int weight)
{
    if(exists(i, j))    return;
    E[i][j] = new edge(edge, weight);
    V[i].out_degree++;
    V[j].in_degree++;
    e++;
}

template<typename Tv, typename Te>
inline Te graph_matrix<Tv, Te>::remove(int i, int j)
{
    Te eBak = edge(i, j);
    V[i].out_degree--;
    V[i].in_degree--;
    delete E[i][j];
    E[i][j] = NULL;
    e--;
    return eBak;
}

template<typename Tv, typename Te>
inline int graph_matrix<Tv, Te>::insert(const Tv& v)
{
    for(int i = 0; i < n; i++)
        E[i].insert(NULL);
    n++;
    E.insert(vec<edge<Te>*>(n, n, NULL)); // 添加一个容量，长度为n，初值为NULL 的边记录
    return V.insert(vertex<Tv>(v));
}

template<typename Tv, typename Te>
inline Tv graph_matrix<Tv, Te>::remove(int i)
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
    Tv vBad = vertex(i);
    V.remove(i);
    return vBak;
}