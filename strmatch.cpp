#include<cstring>
#include<iostream>
#include<algorithm>
#include<climits>

int* build_next(char *p)
{
    int m = strlen(p), j = 0;
    int *N = new int[m];
    int t = N[0] = -1;
    while(j < m - 1)
    {
        if(t < 0 || p[j] == p[t])
        {   
            t++, j++;
            N[j] = p[j] != p[t] ? t : N[t];
            #ifdef V1
            N[j] = t;
            #endif
        }
        else    t = N[t];
    }
    return N;
}

int kmp_match(char *P, char *T)
{
#ifdef COUNT
int cnt = 0;
#endif
    int *next = build_next(P);
    int n = strlen(T), i = 0;
    int m = strlen(P), j = 0;
    while(i < n && j < m)
    {
        if(j < 0 || P[j] == T[i])
        {   
            i++, j++;
            #ifdef COUNT
            cnt++;
            #endif
        }
        else
            j = next[j];
    }
    delete [] next;
    // 如果 (i - j) 大于 (n - m) 则匹配失败
    #ifdef COUNT
    std::cout << "进行了" << cnt << "次对比" << std::endl;
    #endif
    return i - j;
}

int* buildBC(char *p)
{
    int m = strlen(p);
    int *bc = new int[256];
    for(int i = 0; i < 256; i++)
    {   bc[i] = -1; }
    for(int i = 0; i < m; i++)
    {   bc[p[i]] = i;   }
    return bc;
}

int* buildSS(char *p)
{
    int m = strlen(p);
    int *ss = new int[m];
    ss[m - 1] = m;
    for(int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j--)
    {
        if((lo < j) && ss[m - hi + j - 1] <= j - lo)
            ss[j] = ss[m - hi + j - 1];
        else
        {
            hi = j, lo = std::min(lo, hi);
            // 对比 p[lo, hi] 段的字符是否相等
            while((lo >= 0) && (p[lo] == p[m - hi + lo - 1]))
                lo--;
            ss[j] = hi - lo;    // 此时 ss[j] = 两端的差
        }
    }
    return ss;
}

int* buildGS(char *p)
{
    int *ss = buildSS(p);
    int m = strlen(p);
    int * gs = new int[m];
    for(int i = 0; i < m; i++)  gs[i] = m;
    for(int i = 0, j = m - 1; j < UINT_MAX; j--)
    {
        if(j + 1 == ss[j])
            while(i < m - j - 1)
                gs[i++] = m - j - 1;
    }
    for(int j = 0; j < m - 1; j++)
        gs[m - ss[j] - 1] = m - j - 1;
    delete [] ss;
    return gs;
}

int bm_match(char *p, char *t)
{
    int * bc = buildBC(p);
    int * gs = buildGS(p);
    int i = 0;
    int n = strlen(t), m = strlen(p);
#ifdef COUNT
int cnt = 0;
#endif
    while(m + i <= n)
    {
        int j = m - 1;
        // 从右向左匹配
        while(p[j] == t[i + j])
        {
            if(0 > --j) break;
            #ifdef COUNT
            cnt++;
            #endif
        }
        // 若 j < 0 说明模式串匹配完成
        if(j < 0)   break;
        else    // 否则适当移动模式串
            i += std::max(gs[j], j - bc[t[i + j]]);
    }
#ifdef COUNT
std::cout << "进行了" << cnt << "次对比" << std::endl;
#endif
    delete [] gs; delete [] bc;
    return i;
}