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
const int N = 12;  // size for global arrays (if needed)
#else
const int N = 2e5 + 5;  // size for global arrays (if needed)
#endif

#define var(x) (2 * x - 1);
#define neg(x) (((2 * x) ^ 1) - 1)

vi G[N];
bool vis[N];
bool on_stack[N];
vi low_link(N, -1);
vi dfs_num(N, -1);
int idx = 1;
vvi dag;
vi scc_id(N, -1);
stack<int> S;

void dfs(int u)
{
    low_link[u] = dfs_num[u] = idx++;
    S.push(u);
    on_stack[u] = true;
    vis[u] = true;
    for (auto v : G[u]) {
        if (!vis[v]) {
            dfs(v);
            low_link[u] = min(low_link[u], low_link[v]);  // propagate.
        } else if (on_stack[v])                           // an back edge
            low_link[u] = min(low_link[u], dfs_num[v]);  // why not low_link[v]? because low_link[v]
                                                         // might not have been finalize yet
    }

    if (low_link[u] == dfs_num[u]) {
        vi scc;
        while (S.size()) {
            int v = S.top();
            S.pop();
            on_stack[v] = false;
            scc.push_back(v);
            scc_id[v] = dag.size();
            if (v == u) break;
        }
        dag.push_back(scc);
    }
}

void tarjan(int m)
{
    for (int i = 1; i <= 2 * m; i++) {
        if (!vis[i]) dfs(i);
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    while (n--) {
        char neg1, neg2;
        int x1, x2;
        cin >> neg1 >> x1 >> neg2 >> x2;
        int u = 2 * x1 - (neg1 == '+' ? 1 : 0);
        int nu = 2 * x1 - (neg1 == '+' ? 0 : 1);
        int v = 2 * x2 - (neg2 == '+' ? 1 : 0);
        int nv = 2 * x2 - (neg2 == '+' ? 0 : 1);
        dbg(u, "->", nv);
        G[u].push_back(nv);  // u → ¬v
        dbg(v, "->", nu);
        G[v].push_back(nu);  // v → ¬u
    }

    tarjan(m);
    reverse(all(dag));
    dbg(dag);
    dbg(dfs_num);
    dbg(low_link);
    dbg(scc_id);
    for (int i = 1; i <= 2 * m; i += 2) {
        if (scc_id[i] == scc_id[i + 1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    vi val(m * 2 + 2, -1);
    for (auto scc : dag) {
        for (auto u : scc) {
            if (val[u] != -1) continue;
            val[u] = 1;
            if (u % 2 == 0)
                val[u + 1] = 0;
            else
                val[u - 1] = 0;
        }
    }

    dbg(val);

    for (int i = 1; i <= 2 * m; i += 2) {
        if (val[i])
            cout << "+";
        else
            cout << "-";
        cout << " ";
    }
    return 0;
}