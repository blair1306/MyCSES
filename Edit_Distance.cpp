#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef long long ll;

const int M = 1e9 + 7;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    string s1;
    string s2;
    int n1, n2;

    cin >> s1;
    cin >> s2;

    n1 = s1.length();
    n2 = s2.length();

    vvi dp(n1 + 1, vi(n2 + 1));

    for (int i = 0; i <= n1; i++)
    {
        for (int j = 0; j <= n2; j++)
        {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else
            {
                int ins, del, rep;
                ins = dp[i][j - 1] + 1;
                del = dp[i - 1][j] + 1;
                rep = dp[i - 1][j - 1];
                if (s1[i - 1] != s2[j - 1])
                    rep++;
                dp[i][j] = min({ins, del, rep});
            }
        }
    }

    cout << dp[n1][n2] << endl;

    return 0;
}