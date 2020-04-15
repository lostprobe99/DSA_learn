#ifndef _PUB_H_
#define _PUB_H_

#include<stdlib.h>

int max(const int x, const int y);

int min(const int x, const int y);

int ctoi(const char ch);

template <typename T>
void swap(T & x, T & y)
{
    T t = x;
    x = y;
    y = t;
}

void quick_sort(int left, int right, int *nums);

char * strcpy(char * dest, size_t destlen, const char * src);

char * strncpy(char * dest, size_t destlen, const char * src, size_t n);

char * strcat(char * dest, const size_t destlen, const char * src);

char * strncat(char * dest, const size_t destlen, const char * src, size_t n);

void del_Lchar(char * str, const char in_char);
void del_Rchar(char * str, const char in_char);
void del_LRchar(char * str, const char in_char);
void del_Mstr(char * str, const char * in_str);
void LPad(char * str, const char in_char, size_t in_len);
void RPad(char * str, const char in_char, size_t in_len);
void toLower(char *str);
void toUpper(char * str);
int isLower(const char *str);
int isUpper(const char *str);
int isDigit(const char *str);
char * get_XMLtag_content( char * XMLstr, char * tagName, char * out_value);
char * get_cur_time(char * fmt, char * out_stime);
int get_year(time_t timer);
int get_mon(time_t timer);
int get_day(time_t timer);
int get_hour(time_t timer);
int get_min(time_t timer);
int get_sec(time_t timer);
int timetostr(const time_t * ti, char * strtime);
int strtotime(char * strtime, time_t * ti);
#endif
