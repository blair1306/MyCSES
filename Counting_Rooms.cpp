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
typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef unsigned long long ull;
typedef vector<ll> vll;

// Shortcuts
#define endl '\n'
#define all(x) (x).begin(), (x).end()

// Constants
const int INF = 1e9 + 5;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; // or 998244353
const int N = 1000;      // size for global arrays (if needed)

// Debugging (remove for submission)
#define DEBUG 0
#define dbg(x) \
    if (DEBUG) \
        cerr << #x << " = " << x << endl;

char dp[N + 2][N + 2];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> dp[i][j];
        }
    }

    int ans = 0;
    queue<pii> q;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (dp[i][j] == '#')
                continue;
            ans++;
            q.push({i, j});

            while (!q.empty())
            {
                int x, y;
                tie(x, y) = q.front();
                q.pop();
                if (dp[x][y] == '#' || dp[x][y] == 0)
                    continue;
                dp[x][y] = '#';
                q.push({x + 1, y});
                q.push({x, y + 1});
                q.push({x - 1, y});
                q.push({x, y - 1});
            }
        }
    }

    cout << ans << endl;

    return 0;
}