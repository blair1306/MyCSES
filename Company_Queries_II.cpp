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

struct edge {
    int v, eid;
};

vector<edge> tree[N];
vi node_id;
vi node_depth;
vi id_map(N, -1);
vi vis(2 * N);
vi segtree;

void addEdge(int u, int v)
{
    static int _id = 0;
    tree[u].push_back({v, _id++});
}

void dfs(int u, int depth)
{
    vis[u] = 1;
    if (id_map[u] == -1) id_map[u] = node_id.size();
    node_id.push_back(u);
    node_depth.push_back(depth);
    for (auto [v, eid] : tree[u]) {
        if (vis[v]) continue;
        vis[v] = 1;
        dfs(v, depth + 1);
        node_id.push_back(u);
        node_depth.push_back(depth);
    }
}

int getLCA(int l, int r)  // [l, r)
{
    int n = node_id.size();
    l += n;
    r += n;
    int lca = l;
    while (l < r) {
        if (l & 1) {
            if (node_depth[segtree[l]] < node_depth[segtree[lca]]) lca = l;
            l++;
        }
        if (!(r & 1)) {
            if (node_depth[segtree[r]] < node_depth[segtree[lca]]) lca = r;
            r--;
        }
        l = l >> 1;
        r = r >> 1;
    }
    return node_id[segtree[lca]];
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int e;
        cin >> e;
        addEdge(e, i);
    }

    dfs(1, 0);

    n = node_id.size();
    segtree.resize(n * 2);
    for (int i = 0; i < n; i++) {
        segtree[i + n] = i;
    }

    for (int i = n - 1; i > 0; i--) {
        int l = segtree[i << 1];
        int r = segtree[i << 1 | 1];
        if (node_depth[l] > node_depth[r]) swap(l, r);
        segtree[i] = l;
    }
    dbg(node_id);
    dbg(node_depth);
    dbg(id_map);
    dbg(segtree);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a = id_map[a];
        b = id_map[b];
        if (a > b) swap(a, b);
        b++;
        cout << getLCA(a, b) << endl;
    }

    return 0;
}