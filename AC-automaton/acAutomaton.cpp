#include <iostream>
#include <queue>

using namespace std;

class solution
{
public:
    static const int MAX_LENGTH_OF_MATCH = 10010; // 模式串最大长度
    static const int CHARACTER_NUMBER = 26;       // 26个字母

    // Trie树
    struct Trie
    {
        /* data */
        // Trie树节点数组
        int next[MAX_LENGTH_OF_MATCH][CHARACTER_NUMBER]; // next[i][j] 表示 Trie 树节点 i 的 j 子节点编号，即 i 的第 j 个子节点编号，值-1 表示节点 i 没有第 j 个子节点

        // 失效节点数组
        int fail[MAX_LENGTH_OF_MATCH]; // fail[i] 表示节点 i 的失效指针指向的节点编号

        //  Trie 树节点的结束标记
        int end[MAX_LENGTH_OF_MATCH]; // 每当一个一个字符串在节点i结束，end[i]就会递增.

        int root; // 根节点
        int L;    // Trie 树中节点数量+1，即指向下一个加入的节点所在的位置

        // 节点初始化
        int newNode()
        {
            for (int i = 0; i < CHARACTER_NUMBER; i++)
            {
                next[L][i] = -1;
            }
            end[L++] = 0;
            return L - 1;
        }

        // 初始化
        void init()
        {
            L = 0;
            root = newNode();
        }

        // 插入
        void insert(char buf[])
        {
            int len = strlen(buf);
            int now = root;
            for (int i = 0; i < len; i++)
            {
                if (next[now][buf[i] - 'a'] == -1)
                {
                    next[now][buf[i] - 'a'] = newNode();
                }
                now = next[now][buf[i] - 'a'];
            }
            end[now]++;
        }

        // 构建fail数组
        void build()
        {
            // 用队列实现层次遍历
            queue<int> Q;
            fail[root] = root;

            // 先对根节点的子节点建立fail数组
            for (int i = 0; i < CHARACTER_NUMBER; i++)
            {
                if (next[root][i] == -1)
                {
                    next[root][i] = root;
                }
                else
                {
                    fail[next[root][i]] = root;
                    Q.push(next[root][i]);
                }

                // 利用队列先进先出的特点，来实现层次遍历。
                while (!Q.empty())
                {
                    int now = Q.front();
                    Q.pop();

                    for (int i = 0; i < CHARACTER_NUMBER; i++)
                    {
                        if (next[now][i] == -1)
                        {
                            next[now][i] = next[fail[now]][i];
                        }
                        else
                        {
                            fail[next[now][i]] = next[fail[now]][i];
                            Q.push(next[now][i]);
                        }
                    }
                }
            }
        }

        // 查询部分实现的功能是统计与主串匹配的模式串的数量（不重复计数）
        int query(char buf[])
        {
            int len = strlen(buf);
            int res = 0;
            int now = root;

            for (int i = 0; i < len; i++)
            {
                now = next[now][buf[i] - 'a'];
                int temp = now;

                // 利用temp变量回溯，注意end数组会发生改变，需要重新进行初始化，如果不是极致性能要求且只进行一次匹配的话建议对end进行拷贝。
                while (temp != root)
                {
                    res += end[temp];
                    end[temp] = 0;
                    temp = fail[temp];
                }
            }
            return res;
        }
    };
};