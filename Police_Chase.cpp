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
const int N = 500 + 1;  // size for global arrays (if needed)
#endif

int n;
vi g[N];
int cap[N][N];
vi parent(N);
vi vis(N);

void dfs(int u)
{
    if (vis[u]) return;
    vis[u] = 1;
    for (int v : g[u]) {
        if (cap[u][v] <= 0) continue;
        dfs(v);
    }
}

bool bfs()
{
    fill(all(parent), 0);
    queue<int> q;
    q.push(1);

    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            int capacity = cap[u][v];
            if (parent[v] || capacity <= 0) continue;
            q.push(v);
            parent[v] = u;
        }
    }

    return parent[n];
}

int edmondsKarp()
{
    int maxFlow = 0;
    while (bfs()) {
        int u = n, v;
        while (u != 1) {
            v = u;
            u = parent[u];
            cap[u][v] -= 1;
            cap[v][u] += 1;
        }
        maxFlow++;
    }

    return maxFlow;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m;
    int maxFlow;
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        cap[a][b] = 1;
    }

    maxFlow = edmondsKarp();

    dfs(1);
    cout << maxFlow << endl;
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (vis[u] && !vis[v] && cap[v][u] > 0) {
                cout << u << " " << v << endl;
            }
        }
    }

    return 0;
}