/**
 * KMP字符串匹配算法
 *视频学习网址:https://search.bilibili.com/all?vt=52478028&keyword=kmp%E7%AE%97%E6%B3%95&from_source=webtop_search&spm_id_from=333.1007&search_source=2
 */
#include <iostream>
using namespace std;

const int MAX_MATCH_LENGTH = 10010;       // 模式串最大长度
static const int MAX_MAIN_LENGTH = 10010; // 主串最大长度

// 模式串next数组（预处理）
int kmp_next[MAX_MATCH_LENGTH]; // kmp_next[k] = x; 表示对于模式串字符串match而言，match[k]字符之前的子串的最大公共前后缀 即：（match[0] = match[k - 1] .... match[x-1] = match[k - x])

/**
 * 模式串预处理函数，生成模式串的next数组.
 */
void kmp_pre(char x[], int m, int kmpNext[])
{
    int i;               // 模式串遍历下标。
    int j;               // （重要） 为next[i]赋值的变量,含义与kmp_next数组元素相同
    j = kmpNext[0] = -1; // 含义为match[0]的前缀字符子串为空
    i = 0;

    // 遍历数组match
    while (i < m)
    {
        // 注意此处 -1 ！= j的含义，是指目前的x[j]已经是x[0]，即模式串第一个字符。
        while (-1 != j && x[i] != x[j])
        {
            j = kmpNext[j]; // 如果x[i] != x[j]，则查询x[j]的字符子串的最大公共字符前后缀的长度，并让j指向该最大公共字符前缀的后面一个字符。
        }
        kmpNext[++i] = ++j;
    }
}

int kmp(char match[], int matchLen, char main[], int mainLen)
{
    int i = 0; // main字符串遍历下标
    int j = 0; // match字符串遍历下标

    int ans = 0;

    kmp_pre(match, matchLen, kmp_next);

    while (i < mainLen)
    {
        // 这里的-1 != j含义为模式串第一个字符就与当前主串待匹配字符main[i]不同
        while (-1 != j && main[i] != match[j])
        {
            j = kmp_next[j];
        }

        i++;
        j++;

        if (j > matchLen)
        {
            ans++;
            j = kmp_next[j];
        }
    }
    return ans;
}