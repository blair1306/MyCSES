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

vi G[N];
bool vis[N];
bool on_stack[N];
vi low_link(N, -1);
vi dfs_num(N, -1);
int idx = 1;
vvi dag;
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
        bool neg1, neg2;
        int x1, nx1, x2, nx2;
        char neg;
        cin >> neg;
        if (neg == '+')
            neg1 = false;
        else
            neg1 = true;
        cin >> x1;
        cin >> neg;
        if (neg == '+')
            neg2 = false;
        else
            neg2 = true;
        cin >> x2;
        x1 = 2 * x1 - 1;
        if (neg1) {
            nx1 = x1;
            x1++;
        } else {
            nx1 = x1 + 1;
        }
        x2 = 2 * x2 - 1;
        if (neg2) {
            nx2 = x2;
            x2++;
        } else
            nx2 = x2 + 1;
        // x1 -> not x2
        G[x1].push_back(nx2);
        dbg(x1, "->", nx2);
        // x2 -> not x1
        dbg(x2, "->", nx1);
        G[x2].push_back(nx1);
    }

    tarjan(m);
    dbg(dag);
    dbg(dfs_num);
    dbg(low_link);
    for (int i = 1; i <= 2 * m; i += 2) {
        if (low_link[i] == low_link[i + 1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    vi val(m * 2 + 2, -1);
    for (auto scc : dag) {
        int b = 1;
        for (auto u : scc) {
            if ((u % 2 == 0) && val[u] != -1) {
                b = !val[u];
                break;
            }
        }
        for (auto u : scc) {
            val[u] = b;
        }
    }

    for (int i = 1; i <= 2 * m; i += 2) {
        if (val[i])
            cout << "+";
        else
            cout << "-";
        cout << " ";
    }
    return 0;
}