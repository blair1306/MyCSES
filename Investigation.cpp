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
vi dp1(N, INF);
vi dp2(N, 0);
vi state(N, 0);
vi order;

int min_d = INF;
int max_d = 0;

void dfs(int u)
{
    state[u] = 1;
    for (auto v : pre[u]) {
        if (state[v] == 0) {
            dfs(v);
        }
    }
    order.push_back(u);
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
    dp1[1] = 0;
    dp2[1] = 0;
    dfs(n);
    // we don't need to reverse order because it's already reversed
    dbg(order);
    for (int u : order) {
        for (auto [w, v] : wG[u]) {
            // if (d[u] + w == d[v]) {  // is in shortest path
            {
                dp[v] = (dp[v] + dp[u]) % MOD;
                dp1[v] = min(dp1[v], dp1[u] + 1);
                dp2[v] = max(dp2[v], dp2[u] + 1);
            }
        }
    }

    dbg(dp, dp1, dp2);

    cout << d[n] << ' ' << dp[n] << ' ' << dp1[n] << ' ' << dp2[n] << endl;
    return 0;
}