#if defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
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

// #define LOCAL
#ifdef LOCAL
#include "mydebug.h"
#else
#define dbg(...)
#define dbg_arr(...)
#endif

// Constants
const int INF = 1e9 + 5;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;  // or 998244353
#ifdef LOCAL
const int N = 10 + 1;  // size for global arrays (if needed)
#else
const int N = 1e5 + 1;  // size for global arrays (if needed)
#endif

using wE = pair<ll, int>;
vector<wE> wG[N];
vll d(N, LINF);
vi pre[N];
int n;
vll dp(N, 0);
vi visited(N, 0);
vi dp1(N, INF);
vi dp2(N, 0);

int min_d = INF;
int max_d = 0;

void dfs(int u, int depth)
{
    if (u == 1) {
        min_d = min(min_d, depth);
        max_d = max(max_d, depth);
    }
    if (visited[u]) return;
    visited[u] = 1;
    // dp1[u] = 1;
    // dp2[u] = 1;

    for (auto v : pre[u]) {
        dfs(v, depth + 1);
        dp[u] += dp[v];
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        wG[a].push_back({c, b});
    }

    // dijkstra with modification
    priority_queue<wE, vector<wE>, greater<wE>> q;
    q.push({0, 1});
    d[1] = 0;
    while (q.size()) {
        auto [tmp, u] = q.top();
        q.pop();

        if (d[u] < tmp) continue;

        for (auto [w, v] : wG[u]) {
            ll nw = d[u] + w;
            if (nw <= d[v]) {
                if (nw < d[v]) {
                    pre[v].clear();
                    q.push({nw, v});
                }
                d[v] = nw;
                pre[v].push_back(u);
            }
        }
    }

    dp[1] = 1;
    dfs(n, 0);
    dbg(dp, min_d, max_d);

    cout << d[n] << ' ' << dp[n] << ' ' << min_d << ' ' << max_d << endl;
    return 0;

    dp[1] = 1;
    dp1[1] = 1;
    dp2[1] = 1;
    for (int u = 1; u <= n; u++) {
        if (pre[u].size() == 0) continue;
        int max_pd = 0, min_pd = INF;
        for (auto v : pre[u]) {
            if (pre[u].size() == 1) {
                dp[u] = dp[v];
                dp1[u] = dp1[v];
                dp2[u] = dp2[v];
            } else {
                dp[u] = (dp[u] + dp[v]) % MOD;
                min_pd = min(min_pd, dp1[v]);
                max_pd = max(max_pd, dp2[v]);
            }
        }
        dp1[u] = min(dp1[u], min_pd + 1);
        dp2[u] = max(dp2[u], max_pd + 1);
    }

    dbg(d);
    dbg(pre);
    dbg(dp);
    dbg(dp1);
    dbg(dp2);

    cout << d[n] << ' ';
    cout << dp[n] << ' ';
    cout << dp1[n] << ' ';
    cout << dp2[n] << ' ';

    return 0;
}