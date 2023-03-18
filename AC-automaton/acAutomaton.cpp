#include <iostream>
#include <queue>

using namespace std;

class solution
{
public:
    // 主串最大长度
    static const int MAXN = 10010;

    // 模式串最大长度
    static const int MAXM = 110;

    struct Trie
    {
        /* data */
        // Trie树节点数组
        int next[MAXN][MAXM]; // next[i][j] 表示 Trie 树节点 i 的 j 子节点编号，即 i 的第 j 个子节点编号，-1 表示节点 i 没有第 j 个子节点

        // 失效节点数组
        int fail[MAXN]; // fail[i] 表示节点 i 的失效指针指向的节点编号

        //  Trie 树节点的结束标记
        int end[MAXN];

        int root; // 根节点
        int L;    // Trie 树中节点数量+1，即指向下一个加入的节点所在的位置

        // 初始化一个Trie树节点，返回值为新节点的编号。
        int newNode()
        {
            //
            for (int i = 0; i < MAXM; i++)
            {
                next[L][i] = -1;
            }
            end[L++] = 0;
            return L - 1;
        }

        //
        void init()
        {
            L = 0;
            root = newNode();
        }

        //
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

        //
        void build()
        {
            //
            queue<int> Q;

            fail[root] = root;
            for (int i = 0; i < MAXN; i++)
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

                while (!Q.empty())
                {
                    int now = Q.front();
                    Q.pop();
                    for (int i = 0; i < MAXN; i++)
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
    };
};