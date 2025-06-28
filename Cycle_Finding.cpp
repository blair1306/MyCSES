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

using Edge = vector<tuple<int, int, ll>>;
using Graph = vector<vector<int>>;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    Edge E;
    Graph G(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        E.push_back({a, b, c});
        G[a].push_back(b);
    }

    vll dis(n + 1, LINF);
    dis[1] = 0;
    for (int i = 1; i < n; i++) {
        for (auto &[u, v, w] : E) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
            }
        }
    }

    // vi in_loop(n + 1, 0);
    int loop_start = 0;
    int loop_end = 0;
    bool has_loop = false;
    for (auto &[u, v, w] : E) {
        if (dis[v] > dis[u] + w) {
            has_loop = true;
            loop_start = v;
            loop_end = u;
        }
    }

    if (!has_loop) {
        cout << "NO" << endl;
        return 0;
    }

    // dfs
    vi visited(n + 1, 0);
    vi parent(n + 1, 0);

    queue<int> q;
    q.push(loop_start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == loop_end) break;
        for (auto &v : G[u]) {
            if (parent[v]) continue;
            parent[v] = u;
            q.push(v);
        }
    }
    dbg(loop_start, loop_end, parent);

    vi loop;
    cout << "YES" << endl;
    int tmp = loop_end;
    while (loop_end != 0) {
        loop.push_back(loop_end);
        loop_end = parent[loop_end];
    }
    reverse(all(loop));
    cout << tmp << ' ';
    for (auto u : loop) {
        cout << u << ' ';
    }
    cout << endl;

    return 0;
}