#include"graph_matrix.h"
#include"graph.h"
#include<limits.h>

template<typename Tv, typename Te>
inline graph_matrix<Tv, Te>::graph_matrix()
{   n = e = 0;  }

template<typename Tv, typename Te>
graph_matrix<Tv, Te>::~graph_matrix()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            delete E[i][j];
}

template<typename Tv, typename Te>
inline Tv& graph_matrix<Tv, Te>::vertex(int i)
{   return V[i].data;   }

template<typename Tv, typename Te>
inline int graph_matrix<Tv, Te>::inDegree(int i)
{   return V[i].in_degree;  }

template<typename Tv, typename Te>
inline int graph_matrix<Tv, Te>::outDegree(int i)
{   return V[i].out_degree; }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::fTime(int i)
{   return V[i].ftime;  }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::dTime(int i)
{   return V[i].dtime;  }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::parent(int i)
{   return V[i].parent;  }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::priority(int i)
{   return V[i].priority;  }

template<typename Tv, typename Te>
inline vstatus& graph_matrix<Tv, Te>::status(int i)
{   return V[i].status;  }

template<typename Tv, typename Te>
inline bool graph_matrix<Tv, Te>::exists(int i, int j)
{
    return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j];
}

template<typename Tv, typename Te>
inline etype& graph_matrix<Tv, Te>::type(int i, int j)
{   return E[i][j]->type;   }

template<typename Tv, typename Te>
inline int& graph_matrix<Tv, Te>::weight(int i, int j)
{   return E[i][j]->weight; }

template<typename Tv, typename Te>
inline Te& graph_matrix<Tv, Te>::edge(int i, int j)
{   return E[i][j]->data;   }

template<typename Tv, typename Te>
inline void graph_matrix<Tv, Te>::insert(int i, int j, const Te& edge, int weight)
{
    E[i][j] = new edge(edge, weight);
    V[i].out_degree++;
    V[j].in_degree++;
}