/**
 * 2023/3/16 xyxzs
 * 最长回文子串-马拉车算法。
 * 视频资源：https://www.bilibili.com/video/BV1Ks4y1t7c6/?spm_id_from=333.337.search-card.all.click
 * 但说实话这个视频我觉得一般般，马拉车算法我觉得很难理解，所以我尽量把每个变量的含义和算法原理注释清除。
 */
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 110010;

// 对原数组进行处理后得到的新数组。
char Ma[MAXN * 2];

// 新数组的最大回文半径数组
int Mp[MAXN * 2]; // Mp[i]:表示Ma[i]附近可以组成回文字符串的最大半径数 如: Ma = ['$','#','a','#'],则对应的Mp=[1,1,2,1]

/**
 *输入参数：字符串s，字符串长度len
 */
void Manacher(char s[], int len)
{
    int l = 0; // 记录Ma数组长度
    Ma[l++] = '$';
    Ma[l++] = '#';

    /*
        将原字符串进行处理，生成一个新数组 Ma，其前两个元素分别为 $ 和 #，接下来第 2*i-1
    减号位置上放对应的字符。例如，对于 s = "aba"，生成新数组 Ma = '$ # a # b # a # '。
    */
    for (int i = 0; i < len; i++)
    {
        Ma[l++] = s[i];
        Ma[l++] = '#';
    }
    Ma[l] = '#'; // 最后一个Ma
    int mx = 0;  // 已知回文字符串最右端位置。
    int id = 0;  // 已知回文字符串中心位置。

    for (int i = 0; i < l; i++)
    {
        Mp[i] = (mx > i) ? min(Mp[2 * id - i], mx - i) : 1; // 初始化Mp[i]，mx > i对应Ma[i]在已知最大回文串之中。

        // 暴力扩展,找到Ma[i]为中心的最大回文子串半径
        while (Ma[i + Mp[i]] == Ma[i - Mp[i]])
        {
            Mp[i]++;
        }

        // i + Mp[i] > mx 说明产生了新的最长子回文串，更新mx和id的值
        if (i + Mp[i] > mx)
        {
            mx = i + Mp[i];
            id = i;
        }
    }
}

// 主串
char s[MAXN];

int main()
{
    // 这个是啥意思？
    while (scanf("%/s", s) == 1)
    {
        int len = strlen(s);
        Manacher(s, len);
        int ans = 0;
        for (int i = 0; i < len * 2 + 2; i++)
        {
            /**
             * 解释一下为什么是Mp[i]-1
             * 原来的数组经过处理，长度变成了2 * len + 2(多了第一个和最后一个),因而最大回文半径也变成了两倍。
             */
            ans = max(ans, Mp[i] - 1);
        }
        printf("%/d\n", ans);
    }
    return 0;
}