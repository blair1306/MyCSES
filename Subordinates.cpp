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
const int N = 2e5 + 1;  // size for global arrays (if needed)
#endif

int subord_cnt[N];
using Graph = vector<vector<int>>;

void dfs(Graph &G, int r, int p)
{
    int u = r;
    if (G[u].size() == 0) {
        subord_cnt[u] = 0;
        return;
    }
    for (auto v : G[r]) {
        // if (v == p) continue;
        dfs(G, v, u);
        subord_cnt[u] += subord_cnt[v] + 1;
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    cin >> n;
    Graph G(n + 1);

    for (int i = 2; i <= n; i++) {
        int sup;
        cin >> sup;
        G[sup].push_back(i);
    }

    dbg(G);
    dfs(G, 1, -1);

    for (int i = 1; i <= n; i++) {
        cout << subord_cnt[i] << ' ';
    }
    cout << endl;
    return 0;
}