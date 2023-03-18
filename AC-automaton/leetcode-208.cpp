/**
 * leetcode208是一道前缀树的问题，并不是ac自动机的多模式匹配，但我暂时也就找到这个来练手。
 * 注意我的内存消耗很大，但是改良数据结构是可以进一步缩小空间的（代价可能是时间变慢）。
 * 前缀树无需维护失效数组（fail），但这会导致匹配时发生访问end[-1]的情况，这是因为在newNode时子节点的值全部被设置为-1.
 * 所以在匹配时记得判断now的值是否为-1，以防止数组访问越界。
 */

class Trie
{
public:
    static const int MAX_LENGTH_OF_STRING = 100000;
    static const int CHARACTER_SIZE = 26;
    int next[MAX_LENGTH_OF_STRING][CHARACTER_SIZE];
    int end[MAX_LENGTH_OF_STRING];
    int root;
    int L;

    Trie()
    {
        L = 0;
        root = newNode();
    }

    void insert(string word)
    {
        int now = root;

        for (char ch : word)
        {
            if (next[now][ch - 'a'] == -1)
            {
                next[now][ch - 'a'] = newNode();
            }

            now = next[now][ch - 'a'];
        }
        end[now]++;
    }

    bool search(string word)
    {
        int now = root;

        for (char ch : word)
        {
            now = next[now][ch - 'a'];
            if (now == -1)
            {
                return false;
            }
        }
        if (now == root || end[now] == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool startsWith(string prefix)
    {
        int now = root;

        for (char ch : prefix)
        {
            now = next[now][ch - 'a'];
            if (now == -1)
            {
                return false;
            }
        }

        if (now == root)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    int newNode()
    {
        for (int i = 0; i < CHARACTER_SIZE; i++)
        {
            next[L][i] = -1;
        }
        end[L++] = 0;
        return L - 1;
    }
};
