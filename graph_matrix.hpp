#include"graph_matrix.h"
#include<limits.h>

template<typename Tv, typename Te>
graph_matrix<Tv, Te>::graph_matrix()
{
    n = e = 0;
}

template<typename Tv, typename Te>
graph_matrix<Tv, Te>::~graph_matrix()
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            delete E[i][j];
}
