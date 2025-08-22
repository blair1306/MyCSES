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

using vp = vector<pii>;  // depth, node

class RMQ {
    vp segtree;
    uint n;  // length of segment tree;

public:
    RMQ(vp &tour)
    {
        assert(tour.size());
        n = 1;
        while (n <= tour.size()) n <<= 1;
        segtree.resize(2 * n);
        for (uint i = 0; i < tour.size(); i++) {
            segtree[i + n] = tour[i];
        }

        for (int i = n - 1; i > 0; i--) {
            segtree[i] = min(segtree[i << 1], segtree[i << 1 | 1]);
        }
        dbg(segtree);
    }

    int query(int left, int right)  // [left, right]
    {
        pii res = {INF, INF};
        for (left += n, right += n; left <= right; left >>= 1, right >>= 1) {
            dbg(left, right);
            if (left & 1) res = min(res, segtree[left++]);
            if (!(right & 1)) res = min(res, segtree[right--]);
        }

        return res.second;  // node
    }
};

vp tour;
vi tour_id(N, -1);
vi tree[N];
vi depths(N, -1);

void dfs(int u, int p, int d)
{
    if (tour_id[u] == -1) {
        tour_id[u] = tour.size();
        depths[u] = d;
    }
    tour.push_back({d, u});
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        tour.push_back({d, u});
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    while (n-- > 1) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, -1, 0);
    RMQ rmq(tour);

    while (q--) {
        int a, b, left, right;
        cin >> a >> b;
        left = tour_id[a];
        right = tour_id[b];
        if (left > right) swap(left, right);
        int lca = rmq.query(left, right);
        int dis = depths[a] + depths[b] - 2 * depths[lca];

        dbg(a, b, lca);

        cout << dis << endl;
    }

    return 0;
}