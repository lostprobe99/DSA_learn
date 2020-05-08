#include<cstring>

int* build_next(char *p)
{
    int m = strlen(p), j = 0;
    int *N = new int[m];
    int t = N[0] = -1;
    while(j < m - 1)
    {
        if(t < 0 || p[j] == p[t])
        {   t++, j++;   N[j] = t;}
        else    t = N[t];
    }
    return N;
}

int kmp_match(char *P, char *T)
{
    int *next = build_next(P);
    int n = strlen(T), i = 0;
    int m = strlen(P), j = 0;
    while(i < n && j < m)
    {
        if(j < 0 || P[j] == T[i])
        {   i++, j++;   }
        else
            j = next[j];
    }
    delete next;
    // 如果 (i - j) 大于 (n - m) 则匹配失败
    return i - j;
}