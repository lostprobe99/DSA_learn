#include"../graph_matrix.hpp"
#include<iostream>
using std::cout;
using std::endl;
int main()
{
    graph_matrix<int, int> g1;
    g1.insert(3);
    cout << "count of vertexs is " << g1.n << endl;
    cout << "count of edges is " << g1.e << endl;

    return 0;
}