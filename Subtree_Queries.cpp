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

vi tree[N];
vll subtree_sum(N, 0);
vi node_val(N, 0);
vi parent(N, -1);

void dfs(int u, int p)
{
    if (parent[u] == -1) parent[u] = p;
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
        subtree_sum[u] += subtree_sum[v];
    }
}

void modify(int u, ll val)
{
    ll diff = val - node_val[u];
    subtree_sum[u] += diff;
    while (u > 0) {
        u = parent[u];
        subtree_sum[u] += diff;
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        node_val[i] = val;
        subtree_sum[i] = val;
    }

    while (n-- > 1) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dbg(tree);
    dfs(1, 0);

    while (q--) {
        int t, a, val;
        cin >> t;
        if (t == 1) {
            cin >> a >> val;
            modify(a, val);
        }
        if (t == 2) {
            cin >> a;
            cout << subtree_sum[a] << endl;
        }
    }

    return 0;
}