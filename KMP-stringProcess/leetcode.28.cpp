#include <string>
using namespace std;

class Solution
{
public:
    int next[10000];
    // 预处理函数
    void kmp_pre(string needle, int m)
    {
        int i;
        int j;
        j = next[0] = -1;
        i = 0;

        while (i < m)
        {
            while (-1 != j && needle[i] != needle[j])
                j = next[j];
            next[++i] = ++j;
        }
    }

    int strStr(string haystack, string needle)
    {
        int n = haystack.length(); // 主串长度
        int m = needle.length();   // 模式串长度

        int i = 0;
        int j = 0;
        int ans = -1;

        kmp_pre(needle, m);

        while (i < n)
        {
            while (-1 != j && haystack[i] != needle[j])
                j = next[j];
            i++;
            j++;
            if (j >= m)
            {
                return ans = (i - m);
            }
        }
        return ans;
    }
};