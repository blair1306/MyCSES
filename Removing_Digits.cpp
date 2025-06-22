#include <bits/stdc++.h>

using namespace std;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 1; // base case

    for (int i = 1; i <= n && i <= 9; i++)
        dp[i] = 1;

    int num = 0;
    for (int i = 10; i <= n; i++)
    {
        num = i;
        while (num > 0)
        {
            if (num % 10 != 0)
                dp[i] = min(dp[i], dp[i - (num % 10)] + 1);
            num /= 10;
        }
    }

    cout << dp[n];

    return 0;
}