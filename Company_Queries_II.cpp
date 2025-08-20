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

using ETour = vector<pii>;  // depth, node

struct RMQ {
    ETour segtree;
    uint n;
    RMQ(ETour& tour)
    {
        assert(tour.size());
        n = 1;
        while (n <= tour.size()) n *= 2;
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
        pii res = {INF, INF};  // {depth, node}
        left += n;
        right += n;
        while (left <= right) {
            dbg(left, right) if ((left & 1)) res = min(res, segtree[left++]);
            if (!(right & 1)) res = min(res, segtree[right--]);
            left >>= 1;
            right >>= 1;
        }
        return res.second;
    }
};

vi e_tree[N];
ETour tour;

void dfs(int u, int d)
{
    tour.push_back({d, u});
    for (int v : e_tree[u]) {
        dfs(v, d + 1);
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

    for (int e = 2; e <= n; e++) {
        int boss;
        cin >> boss;
        e_tree[boss].push_back(e);
    }

    dfs(1, 0);
    vi first_apperance(n + 1, -1);
    dbg(tour);
    for (uint i = 0; i < tour.size(); i++) {
        auto [d, e] = tour[i];
        if (first_apperance[e] == -1) first_apperance[e] = i;
    }
    dbg(first_apperance);

    RMQ rmq(tour);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int left = first_apperance[a];
        int right = first_apperance[b];
        if (left > right) swap(left, right);
        int lcb = rmq.query(left, right);
        cout << lcb << endl;
    }

    return 0;
}