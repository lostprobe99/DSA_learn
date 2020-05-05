/*
 * @Author: lostprobe99 
 * @Date: 2020-05-05 15:21:14 
 * @Last Modified by: lostprobe99
 * @Last Modified time: 2020-05-05 17:13:09
 */
#ifndef _BITMAP_HPP_
#define _BITMAP_HPP_

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

// 位图以一位为一个单位，而 N 是字节数
class Bitmap{
private:
    char * M;
    int N;
protected:
    void init(int n)
    {   M = new char[N = (n + 7) / 8];  memset(M, 0, N);}
public:
    // 按规模创建一个 bitmap
    Bitmap(int n = 8)
    {   init(n);    }
    // 用文件创建一个 bitmap
    Bitmap(const char * const file, int n = 8)
    {
        init(n);
        FILE* fp = fopen(file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
    }
    ~Bitmap()
    {   delete [] M;  M = NULL;    }

    void set(int k)
    {
        expand(k);
        M[k >> 3] |= (0x80 >> (k & 0x07));
    }
    // ~ 位非运算符
    void clear(int k)
    {
        expand(k);
        M[k >> 3] &= ~(0x80 >> (k & 0x07));
    }
    bool test(int k)
    {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07));
    }
    int size() const
    {   return N;   }

    // 导出 bitmap 到文件
    void dump(const char * const filename)
    {
        FILE* fp = fopen(filename, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }
    // 将前 n 为转换为字符串
    char * bits2string(int n)
    {
        expand(n - 1);
        char * s = new char[n + 1];
        s[n] = '\0';
        for(int i = 0; i < n; i++)
            s[i] = test(i) ? '1' : '0';

        return s;
    }
    // 若访问 k 时越界，扩容
    void expand(int k)
    {
        if(k < 8 * N)   return;
        char *oldM = M;
        int oldN = N;
        init(2 * k);
        memcpy(M, oldM, oldN);
        delete [] oldM;
    }
};

#endif