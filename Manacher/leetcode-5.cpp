#include <string>

using namespace std;

class Solution
{
public:
    static const int MAXN = 1010, MAXM = MAXN * 2;
    char Ma[MAXM];
    int Mp[MAXM];

    string Manacher(string s, int len)
    {

        int l = 0;
        char ans[1000];

        Ma[l++] = '$';
        Ma[l++] = '#';

        for (int i = 0; i < len; i++)
        {
            Ma[l++] = s[i];
            Ma[l++] = '#';
        }

        Ma[l] = 0;

        int mx = 0;
        int id = 0;
        Mp[0] = 1;

        for (int i = 1; i < l; i++)
        {
            Mp[i] = ((mx > i) ? (min(Mp[2 * id - i], mx - i)) : 1);

            while ((i - Mp[i]) >= 0 && (i + Mp[i]) < l)
            {
                if (Ma[i + Mp[i]] == Ma[i - Mp[i]])
                {
                    Mp[i]++;
                }
                else
                {
                    break;
                }
            }

            if (i + Mp[i] > mx)
            {
                mx = i + Mp[i];
                id = i;
            }
        }

        int left = 0;
        int right = 0;
        int ansLen = 0;
        for (int i = 0; i < 2 * len + 2; i++)
        {
            if ((Mp[i] - 1) > ansLen)
            {
                ansLen = Mp[i] - 1;
                left = i - Mp[i] + 1;
                right = i + Mp[i] - 1;
            }
        }

        string ansStr = "";

        for (int i = left; i < right; i++)
        {
            if (Ma[i] == '#' || Ma[i] == '$')
            {
                continue;
            }
            else
            {
                ansStr += Ma[i];
            }
        }

        return ansStr;
    }

    string longestPalindrome(string s)
    {
        int len = s.length();
        return Manacher(s, len);
    }
};