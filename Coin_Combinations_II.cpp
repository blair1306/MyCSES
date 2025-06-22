#include <bits/stdc++.h>

using namespace std;

const int M = 1e9 + 7;

int main()
{
    int x;
    int n;

    cin >> n >> x;

    vector<int> coins(n, 0);
    vector<int> dp(x + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    // sort(coins.begin(), coins.end());

    for (int coin : coins)
    {
        for (int i = coin; i <= x; i++)
        {
            dp[i] = (dp[i] + dp[i - coin]) % M;
        }
    }

    cout << dp[x] << endl;

    return 0;
}