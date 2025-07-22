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
vi G[N], cG[N];  // cG for condensed Graph
vi cId(N);
vi vis(N);
vi dfsNum(N);
int cnt = 1;
vi low(N);
stack<int> S;
vi on_stack(N);
vi in_scc(N);
vll dp(N);
vi parent(N);

vvi comp;
vi scc_id(N);
int scc_cnt = 0;

void dfs(int u)
{
    vis[u] = 1;
    dfsNum[u] = low[u] = cnt++;
    S.push(u);
    on_stack[u] = 1;
    for (auto v : G[u]) {
        if (!vis[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (on_stack[v]) {  //
            low[u] = min(low[u], dfsNum[v]);
        }
    }

    if (dfsNum[u] == low[u]) {
        vi scc;
        ll scc_sum = 0;
        while (S.size()) {
            int v = S.top();
            S.pop();
            on_stack[v] = 0;
            scc.push_back(v);
            scc_sum += coin[v];
            if (u == v) break;
        }

        comp.push_back(scc);
        scc_cnt++;
        for (auto v : scc) {
            scc_id[v] = scc_cnt;
        }
        dp[scc_cnt] = scc_sum;
    }
}

void tarjan()
{
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i);
    }
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
    dbg(scc_id);

    for (int u = 1; u <= n; u++) {
        for (auto v : G[u]) {
            if (scc_id[u] == scc_id[v]) continue;
            cG[scc_id[u]].push_back(scc_id[v]);
        }
    }

    dbg(cG);

    fill(all(vis), 0);

    for (int u = scc_cnt; u > 0; u--) {
        ll maxChild = 0;
        for (auto v : cG[u]) {
            maxChild = max(maxChild, dp[v]);
        }
        dp[u] += maxChild;
    }
    dbg(dp);
    ll ans = 0;
    for (auto i : dp) ans = max(i, ans);

    cout << ans << endl;

    return 0;
}