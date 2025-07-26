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

vi eulerTour;

vector<vector<pii>> G;
vi degree;
vi vis;

void dfs(int u)
{
    while (G[u].size()) {
        auto [v, eid] = G[u].back();
        G[u].pop_back();
        if (vis[eid]) continue;
        vis[eid] = 1;
        dfs(v);
    }

    eulerTour.push_back(u);
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    G.resize(n + 1);
    degree.resize(n + 1, 0);
    vis.resize(m + 1, 0);

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back({b, i});
        G[b].push_back({a, i});
        degree[a]++;
        degree[b]++;
    }

    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    dbg(vis);
    dfs(1);
    dbg(vis);
    dbg(G);

    if (eulerTour.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;  // but why? isnt' the above parity test sufficient?
        return 0;
    }

    for (auto a : eulerTour) {
        cout << a << ' ';
    }
    cout << endl;

    return 0;
}