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

using vp = vector<pii>;  // {depth, node}

struct RMQ {
    vp segtree;
    uint n;
    RMQ(vp &tour)
    {
        assert(tour.size());
        n = 1;
        while (n <= tour.size()) n <<= 1;
        segtree.resize(n * 2);
        for (uint i = 0; i < tour.size(); i++) {
            segtree[i + n] = tour[i];
        }
        for (int i = n - 1; i > 0; i--) {
            segtree[i] = min(segtree[i << 1], segtree[(i << 1) | 1]);
        }
        dbg(segtree);
    }

    int query(int left, int right)
    {
        pii res = {INF, INF};
        left += n;
        right += n;
        while (left <= right) {
            if (left & 1) res = min(res, segtree[left++]);
            if (!(right & 1)) res = min(res, segtree[right--]);
            left >>= 1;
            right >>= 1;
        }

        return res.second;
    }
};

vi tree[N];
vi diff(N);
vp tour;
vi depths[N];
vi parent(N);

void dfs(int u, int d, int p)
{
    tour.push_back({d, u});
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, d + 1, u);
        tour.push_back({d, u});
    }
}

void dfs2(int u, int p)
{
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs2(v, u);
        diff[u] += diff[v];
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        parent[b] = a;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0, -1);
    dbg(tour);
    int max_depth = 0;
    vi first_apperance(n + 1, -1);
    for (uint i = 0; i < tour.size(); i++) {
        auto [d, u] = tour[i];
        if (first_apperance[u] == -1) {
            first_apperance[u] = i;
            depths[d].push_back(u);
            max_depth = max(max_depth, d);
        }
    }
    RMQ rmq(tour);

    while (q--) {
        int a, b, left, right;
        cin >> a >> b;
        left = first_apperance[a];
        right = first_apperance[b];
        if (left > right) swap(left, right);
        int lca = rmq.query(left, right);
        int p = 0;
        p = parent[lca];
        diff[a]++;
        diff[b]++;
        diff[lca]--;
        if (p) diff[p]--;
    }

    dbg(diff);

    dfs2(1, 0);

    for (int i = 1; i <= n; i++) cout << diff[i] << " ";
    return 0;
}