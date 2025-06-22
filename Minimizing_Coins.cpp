#include <bits/stdc++.h>
using namespace std;

constexpr int N = 100 * 100 * 100;

int main()
{
    int n; // num of coins;
    int x; // desired sum of $
    int c;
    int ans = -1;

    int coins[100];
    int dp[N + 1];
    fill_n(dp, N + 1, N + 1);

    cin >> n >> x;
    for (int i = 0; i < n; i++)
    {
        cin >> c;
        dp[c] = 1;
        coins[i] = c;
    }

    for (int i = 1; i <= x; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c = coins[j];
            if ((i - c) > 0)
            {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }

    if (dp[x] != N + 1)
    {
        ans = dp[x];
    }

    cout << ans;

    return 0;
}
