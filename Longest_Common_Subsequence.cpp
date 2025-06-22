#if defined(__APPLE__)
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

#elif defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else

#endif

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef long long ll;

const int M = 1e9 + 7;
const int N = 1000;

int dp[N + 1][N + 1];

#define foreach(i, n) for (int i = 0; i < n; i++)
#define DEBUG 1

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n1 = 0;
    int n2 = 0;

    cin >> n1;
    cin >> n2;

    if (n1 < n2)
        swap(n1, n2);

    vi s1(n1);
    vi s2(n2);

    foreach (i, n1)
        cin >> s1[i];
    foreach (i, n2)
        cin >> s2[i];

    foreach (i, n1 + 1)
    {
        foreach (j, n2 + 1)
        {
            if (i == 0 || j == 0)
                continue;
            int a, b, c;
            a = dp[i - 1][j];
            b = dp[i][j - 1];
            c = dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 1 : 0);
            dp[i][j] = max({a, b, c});
            // if (s1[i - 1] == s2[j - 1])
            //     dp[i][j] = 1 + dp[i - 1][j - 1];
            // else
            //     dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    cout << dp[n1][n2] << endl;
    vi ans;
    int len = 1;

    while (n1 > 0 && n2 > 0)
    {
        if (s1[n1 - 1] == s2[n2 - 1])
        {
            ans.push_back(s1[n1 - 1]);
            n1--;
            n2--;
        }
        else if (dp[n1 - 1][n2] > dp[n1][n2 - 1]) // but why?
        {
            n1--;
        }
        else
            n2--;
    }

    reverse(ans.begin(), ans.end());

    for (auto i : ans)
        cout << i << " ";
    cout << endl;

    return 0;
}
