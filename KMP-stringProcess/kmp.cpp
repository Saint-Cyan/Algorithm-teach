/**
 * KMP字符串匹配算法
 *视频学习网址:https://search.bilibili.com/all?vt=52478028&keyword=kmp%E7%AE%97%E6%B3%95&from_source=webtop_search&spm_id_from=333.1007&search_source=2
 * kmp_pre x: [a,a,b] next: [-1,0,1,1]; x: [a,b,c] next: [-1,]
 */
#include <iostream>
using namespace std;

void kmp_pre(char x[], int m, int kmpNext[])
{
    int i;
    int j;
    j = kmpNext[0] = -1;
    i = 0;

    while (i < m)
    {
        while (-1 != j && x[i] != x[j])
            j = kmpNext[j];
        kmpNext[++i] = ++j;
    }
}

int kmp(char x[], int m, char y[], int n)
{
    // x:模式串, y:主串
    int i, j;
    int ans = 0;

    kmp_pre();

    i = j = 0;
    while (i < n)
    {
        while (-1 != j && y[i] != y[j])
            j = kmp_next[j]; // 返回存储在kmp_next中前一个
        i++;
        j++;
        if (j > m)
        {
            ans++;
            j = kmp_next[j];
        }
    }
    return ans;
}