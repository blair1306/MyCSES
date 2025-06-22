#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

const int M = 1e9 + 7;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int m; // upper bound

    cin >> n >> m;
    vvi dp(n + 1, vi(m + 1, 0));

    int num;
    cin >> num;
    if (num != 0)
        dp[1][num] = 1;
    else
    {
        fill(dp[1].begin(), dp[1].end(), 1);
        dp[1][0] = 0;
    }

    for (int i = 2; i <= n; i++)
    {
        cin >> num;
        if (num == 0)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] += dp[i - 1][j];
                dp[i][j] %= M;
                if (j > 1)
                {
                    dp[i][j] += dp[i - 1][j - 1];
                    dp[i][j] %= M;
                }
                if (j < m)
                {
                    dp[i][j] += dp[i - 1][j + 1];
                    dp[i][j] %= M;
                }
            }
        }
        else
        {
            dp[i][num] += dp[i - 1][num];
            dp[i][num] %= M;

            if (num > 1)
            {
                dp[i][num] += dp[i - 1][num - 1];
                dp[i][num] %= M;
            }
            if (num < m)
            {
                dp[i][num] += dp[i - 1][num + 1];
                dp[i][num] %= M;
            }
        }
    }

    int ans = 0;
    if (num == 0)
    {
        for (int i : dp[n])
        {
            ans += i;
            ans %= M;
        }
    }
    else
    {
        ans = dp[n][num];
    }

    cout << ans << endl;

    return 0;
}