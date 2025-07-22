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
const int N = 10;  // size for global arrays (if needed)
#else
const int N = 2e5 + 5;  // size for global arrays (if needed)
#endif

int n;
vi coin(N);
vi G[N];
vi vis(N);
vi dfsNum(N);
int cnt = 1;
vi low(N);
stack<int> S;
vi on_stack(N);
vi in_scc(N);
vi dp(N);
vi parent(N);

vvi comp;

void dfs(int u)
{
    vis[u] = 1;
    dfsNum[u] = low[u] = cnt++;
    S.push(u);
    on_stack[u] = 1;
    for (auto v : G[u]) {
        if (!vis[v]) {
            dfs(v);
            dfsNum[u] = min(dfsNum[u], dfsNum[v]);
        } else {
            dfsNum[u] = min(dfsNum[u], low[v]);
        }
    }

    if (dfsNum[u] == low[u]) {
        vi scc;
        int scc_sum = 0;
        while (S.size()) {
            int v = S.top();
            S.pop();
            on_stack[v] = 0;
            scc.push_back(v);
            scc_sum += coin[v];
            if (u == v) break;
        }

        comp.push_back(scc);
        if (scc.size() > 1) {
            for (auto a : scc) {
                in_scc[a] = 1;
                dp[a] = scc_sum;
            }
        }
    }
}

void tarjan()
{
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i);
    }
}

void dfs1(int u, int p)
{
    vis[u] = 1;
    if (p) dp[u] += dp[p];
    for (auto v : G[u]) {
        if (!vis[v]) dfs1(v, u);
    }
}

int dfs2(int u)
{
    if (dp[u]) return dp[u];
    if (G[u].size() == 0) return coin[u];
    int maxChild = 0;
    for (auto v : G[u]) {
        if (!vis[v]) dfs(v);
        maxChild = max(maxChild, dp[v]);
    }
    dp[u] = maxChild + coin[u];
    return dp[u];
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        coin[i] = c;
    }
    while (m--) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    tarjan();
    dbg(comp);

    fill(all(vis), 0);
    for (int i = 1; i <= n; i++) {
        if (in_scc[i]) {
            vis[i] = 1;
        }
    }

    for (auto scc : comp) {
        if (scc.size() == 1) continue;
        for (auto u : scc) {
            for (auto v : G[u]) {
                if (!vis[v]) dfs1(v, u);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dp[i]) {
            dfs2(i);
        }
    }

    dbg(dp);
    int ans = 0;
    for (auto i : dp) ans = max(i, ans);

    cout << ans << endl;

    return 0;
}