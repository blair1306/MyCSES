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

vi T[N];
vi subtree_size(N, 1);
vll subtree_sum(N, 0);
vll dp(N, 0);
int n;

void dfs(int u, int p)
{
    subtree_size[u] = 1;
    subtree_sum[u] = 0;  // sum of distances from this node to all children
    for (auto v : T[u]) {
        if (v == p) continue;
        dfs(v, u);
        subtree_size[u] += subtree_size[v];
        subtree_sum[u] += subtree_sum[v] + subtree_size[v];
    }
}

void dfs2(int u, int p)
{
    for (auto v : T[u]) {
        if (v == p) continue;
        dp[v] = dp[u] - subtree_size[v] + n - subtree_size[v];
        dfs2(v, u);
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin >> n;
    subtree_size.resize(n + 1);
    subtree_sum.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        T[a].push_back(b);
        T[b].push_back(a);
    }

    dfs(1, 0);
    dp[1] = subtree_sum[1];
    dfs2(1, 0);
    dbg(subtree_size);
    dbg(subtree_sum);
    dbg(dp);

    for (int i = 1; i <= n; i++) {
        cout << dp[i] << ' ';
    }
    cout << endl;

    return 0;
}