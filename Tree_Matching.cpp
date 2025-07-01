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
const int N = 2e5 + 1;  // size for global arrays (if needed)
#endif

vvi Tree(N);
vi dp0(N);  // no match
vi dp1(N);  // match with one child

void dfs(int u, int parent)
{
    dp0[u] = dp1[u] = 0;
    for (int v : Tree[u]) {
        if (v == parent) continue;
        dfs(v, u);
    }

    int sum = 0;
    // no match
    for (int v : Tree[u]) {
        if (v == parent) continue;
        sum += max(dp0[v], dp1[v]);
    }
    dp0[u] = sum;

    // match with v
    for (int v : Tree[u]) {
        if (v == parent) continue;
        dp1[u] = max(dp1[u], 1 + sum + dp0[v] - max(dp0[v], dp1[v]));
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    cin >> n;
    Tree.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        Tree[a].push_back(b);
        Tree[b].push_back(a);
    }

    dfs(1, -1);
    dbg(Tree);
    dbg(dp0);
    dbg(dp1);

    cout << max(dp0[1], dp1[1]) << endl;

    return 0;
}