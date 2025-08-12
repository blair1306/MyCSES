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
const int N = 500 + 5;  // size for global arrays (if needed)
#endif

int n, m;
struct Edge {
    int v, f, c;  // dest, flow, cap
};

vi g[N];
vector<Edge> edgs;
vi lev(N);
vector<uint> ptr(N);
vi route;

void addEdge(int u, int v)
{
    g[u].push_back(edgs.size());
    edgs.push_back({v, 0, 1});
    g[v].push_back(edgs.size());
    edgs.push_back({u, 0, 0});
}

bool bfs()
{
    fill(all(lev), -1);
    queue<int> q;
    q.push(1);
    lev[1] = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int eid : g[u]) {
            auto [v, f, c] = edgs[eid];
            if (lev[v] != -1 || c - f <= 0) continue;
            lev[v] = lev[u] + 1;
            q.push(v);
        }
    }

    return lev[n] != -1;
}

bool dfs(int u)
{
    if (u == n) return true;
    while (ptr[u] < g[u].size()) {
        int eid = g[u][ptr[u]++];
        auto [v, f, c] = edgs[eid];
        if (lev[v] == lev[u] + 1 && c - f > 0 && dfs(v)) {
            edgs[eid].f++;
            edgs[eid ^ 1].f--;
            return true;
        }
    }
    return false;
}

void trace(int u)
{
    route.push_back(u);
    if (u == n) return;

    while (ptr[u] < g[u].size()) {
        int eid = g[u][ptr[u]++];
        auto [v, f, c] = edgs[eid];
        if (f > 0) {
            edgs[eid].f--;
            trace(v);
            return;
        }
    }
}

int dinic()
{
    int k = 0;
    while (bfs()) {
        fill(all(ptr), 0);
        while (dfs(1)) k++;
    }

    return k;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin >> n >> m;
    for (int u, v; m--;) {
        cin >> u >> v;
        addEdge(u, v);
    }

    int ways = dinic();
    cout << ways << endl;
    fill(all(ptr), 0);

    while (ways--) {
        route.clear();
        trace(1);
        cout << route.size() << endl;
        for (int a : route) cout << a << " ";
        cout << endl;
    }

    return 0;
}