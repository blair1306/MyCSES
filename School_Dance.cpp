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
const int N = 500 * 2 + 3;  // size for global arrays (if needed)
#endif

vi g[N];
int cap[N][N];
vi parent(N);

int bfs(int src, int sink)
{
    parent.assign(N, 0);
    queue<int> q;
    q.push(src);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (parent[v] || cap[u][v] <= 0) continue;
            parent[v] = u;
            q.push(v);
        }
    }

    return parent[sink];
}

int edmondsKarp(int src, int sink)
{
    int maxFlow = 0;
    while (bfs(src, sink)) {
        int u = sink, v;
        while (u != src) {
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

    int n, m;
    int k;
    cin >> n >> m >> k;
    int src = n + m + 1;
    int sink = src + 1;
    while (k--) {
        int a, b;
        cin >> a >> b;
        b += n;
        g[src].push_back(a);
        cap[src][a] = 1;
        g[a].push_back(b);
        cap[a][b] = 1;
        g[b].push_back(a);
        cap[b][a] = 1;
        g[b].push_back(sink);
        cap[b][sink] = 1;
    }

    int npairs = edmondsKarp(src, sink);
    cout << npairs << endl;

    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (cap[v][u] > 1) {
                cout << u << " " << v - n << endl;
                continue;
            }
        }
    }

    return 0;
}