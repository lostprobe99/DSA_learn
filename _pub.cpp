/* author       : lostprobe
 * create time  : Sep 15, 2019
 */
#include"_pub.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

//比较两个数，取大者
int max(const int x, const int y)
{   return x > y ? x : y;   }

//比较两个数，取小者
int min(const int x, const int y)
{   return x > y ? y : x;   }

//字符0到9转换为数字0到9，失败返回-1
int ctoi(const char ch)
{
    if(ch >= 48 && ch <= 57)
        return ch - '0';  
    else
        return -1;
}

//快速排序
void quick_sort(int left, int right, int *nums)
{
    if(nums == NULL)
        return;
        
    int i = left, j = right;
    int mid = nums [(i + j) / 2];
    
    while(i < j)
    {
        while(nums[i] < mid)
            i++;
        while(nums[j] > mid)
            j--;
        
        if(i <= j)
        {
            swap(nums[i], nums[j]);
            i++;
            j--;
        }
    }
    
    if(left < j)
        quick_sort(left, j, nums);
    if(right > i)
        quick_sort(i, right, nums);
}

//first rewrite at 14:46 on Oct 6, 2019
//second rewrite at 16:30 on JAN 12, 2020
char * strcpy(char * dest, size_t destlen, const char * src)
{
    memset(dest, 0, destlen);

    int len = min(strlen(src), destlen - 1);
    strncpy(dest, src, len);

    return dest;
}
char * strncpy(char * dest, size_t destlen, const char * src, size_t n)
{
    memset(dest, 0, destlen);

    int len = min(n, destlen - 1);
    strncpy(dest, src, len);

    return dest;
}
char * strcat(char * dest, const size_t destlen, const char * src)
{
    memset(dest + strlen(dest), 0, destlen);
    int left = destlen - 1 - strlen(dest);
    int len = min(strlen(src), left);
    strncat(dest, src, len);
    return dest;
}
char * strncat(char * dest, const size_t destlen, const char * src, size_t n)
{
    memset(dest + strlen(dest), 0, destlen);
    int left = destlen - 1 - strlen(dest);
    int len = min(n, left);
    strncat(dest, src, len);
    return dest;
}

void del_Lchar(char * str, const char in_char)
{
    if(!str)
        return;

    int i = 0;
    for(i = 0; str[i] == in_char; i++)
    ;
    if(i == 0)
        return;
    strcpy(str, str + i);
}
void del_Rchar(char * str, const char in_char)
{
    if(!str)
        return;

    int i = strlen(str) - 1;
    for(; str[i] == in_char; i--)
        str[i] = 0;
}
void del_LRchar(char * str, const char in_char)
{
    del_Lchar(str, in_char);
    del_Rchar(str, in_char);
}

void del_Mstr(char * str, const char * in_str)
{
    if(!str)
        return;

    while(1)
    {
        char * pos = 0;
        pos = strstr(str, in_str);  //在str中搜索in_str
        if(pos == 0)
            break;

        strcpy(pos, pos + strlen(in_str));
    }
}

void LPad(char * str, const char in_char, size_t in_len)
{
    if(strlen(str) >= in_len)
        return;

    int len = in_len - strlen(str);
    strncpy(str + len, str, strlen(str));

    for(int i = 0; i < len; i++)
        str[i] = in_char;
}

void RPad(char * str, const char in_char, size_t in_len)
{
    if(strlen(str) >= in_len)
        return;

    for(size_t i = strlen(str); i < in_len; i++)
        str[i] = in_char;
    
    str[in_len] = 0;
}

void toLower(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}
void toUpper(char * str)
{
    for(size_t i = 0; i < strlen(str); i++)
        str[i] = toupper(str[i]);
}

int isLower(const char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
        if(!islower(str[i]))
            return 0;
    return 1;
}
int isUpper(const char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
        if(!isupper(str[i]))
            return 0;
    return 1;
}
int isDigit(const char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
        if(!isdigit(str[i]))
            return 0;
    return 1;
}

//解析XML标签
char * get_XMLtag_content( char * XMLstr, char * tagName, char * out_value)
{
    //找到开始标签的位置
    char * start = strstr(XMLstr, tagName);
    if(NULL == start)
        return 0;
    
    //找到关闭标签的位置
    char * end = strstr(start + strlen(tagName), tagName);
    if(NULL == end || start >= end)
        return 0;
    
    //确认内容的长度
    start = start + strlen(tagName) + 1;
    end -= 2;
    memcpy(out_value, start, end - start);

    return out_value;
}

/**
 * y-m-d h:m:s
 * y-m-d
 * h:m:s
 * h:m
 */
char * get_cur_time(char * fmt, char * out_stime)
{
    time_t now = time(0);
    struct tm *ttm = localtime(&now);
    if(!strcmp(fmt, "y-m-d h:m:s"))
        sprintf(out_stime, "%04u-%02u-%02u %02u:%02u:%02u",\
        ttm->tm_year + 1900, ttm->tm_mon + 1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
    
    if(!strcmp(fmt, "y-m-d"))
        sprintf(out_stime, "%04u-%02u-%02u",\
        ttm->tm_year + 1900, ttm->tm_mon + 1, ttm->tm_mday);
    
    if(!strcmp(fmt, "y-m"))
        sprintf(out_stime, "%04u-%02u",\
        ttm->tm_year + 1900, ttm->tm_mon + 1);

    if(!strcmp(fmt, "h:m:s"))
        sprintf(out_stime, "%02u:%02u:%02u",\
        ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
    
    if(!strcmp(fmt, "h:m"))
        sprintf(out_stime, "%02u:%02u",\
        ttm->tm_hour, ttm->tm_min);

    return out_stime;
}
int get_year(time_t timer)
{
    struct tm *ttm = localtime(&timer);
    return ttm->tm_year + 1900;
}
int get_mon(time_t timer)
{
    struct tm *ttm = localtime(&timer);
    return ttm->tm_mon + 1;
}
int get_day(time_t timer)
{
    struct tm *ttm = localtime(&timer);
    return ttm->tm_mday;
}
int get_hour(time_t timer)
{
    struct tm *ttm = localtime(&timer);
    return ttm->tm_hour;
}
int get_min(time_t timer)
{
    struct tm *ttm = localtime(&timer);
    return ttm->tm_min;
}
int get_sec(time_t timer)
{
    struct tm *ttm = localtime(&timer);
    return ttm->tm_sec;
}

int timetostr(const time_t * ti, char * strtime)
{
    struct tm * ttm = 0;
    if((ttm = localtime(ti)) == 0)
        return -1;
    
    //0 表示长度不足的在左边补零
    sprintf(strtime, "%04u-%02u-%02u %02u:%02u:%02u",\
    ttm->tm_year + 1900, ttm->tm_mon + 1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
    return 0;
}

// 2019-11-26 18:21:02
// 2019-11-26 18:21:2
// 字符串时间转化为time_t 时间
int strtotime(char * strtime, time_t * ti)
{
    struct tm ttm;
    char tmp[16];
    memset(tmp, 0, sizeof(tmp));
    strncpy(tmp, strtime, 4);
    ttm.tm_year = atoi(tmp);
    ttm.tm_year -= 1900;

    memset(tmp, 0, sizeof(tmp));
    strncpy(tmp, strtime + 5, 2);
    ttm.tm_mon = atoi(tmp);
    ttm.tm_mon -= 1;

    memset(tmp, 0, sizeof(tmp));
    strncpy(tmp, strtime + 8, 2);
    ttm.tm_mday = atoi(tmp);

    memset(tmp, 0, sizeof(tmp));
    strncpy(tmp, strtime + 11, 2);
    ttm.tm_hour = atoi(tmp);

    memset(tmp, 0, sizeof(tmp));
    strncpy(tmp, strtime + 14, 2);
    ttm.tm_min = atoi(tmp);

    memset(tmp, 0, sizeof(tmp));
    strncpy(tmp, strtime + 17, 2);
    ttm.tm_sec = atoi(tmp);

#if 0
    // printf("%d-%d-%d %d:%d:%d\n",\
            ttm.tm_year, ttm.tm_mon, ttm.tm_mday, ttm.tm_hour, ttm.tm_min, ttm.tm_sec);
    *ti = mktime(&ttm);
#endif
    return *ti;
}
