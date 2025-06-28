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

using Edge = vector<tuple<int, int, ll>>;
using Graph = vector<vector<tuple<int, ll>>>;

vll dijkstra(int s, Graph& G, int n)
{
    vll dis(n + 1, LINF);
    vi visited(n + 1, 0);

    dis[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [_, u] = pq.top();
        pq.pop();
        if (visited[u]) continue;
        visited[u] = 1;
        for (auto& [v, w] : G[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({-dis[v], v});
            }
        }
    }

    dbg(dis);

    return dis;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int i;
    int n, m;
    ll ans = LINF;

    cin >> n >> m;
    Edge E;
    Graph G(n + 1);
    Graph rG(n + 1);

    for (i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        E.push_back({a, b, c});
        G[a].push_back({b, c});
        rG[b].push_back({a, c});
    }

    vll dis1 = dijkstra(1, G, n);
    vll disn = dijkstra(n, rG, n);

    for (auto& [u, v, w] : E) {
        if (dis1[u] == LINF || disn[v] == LINF) continue;
        ans = min(ans, dis1[u] + disn[v] + w / 2);
    }

    cout << ans << endl;

    return 0;
}