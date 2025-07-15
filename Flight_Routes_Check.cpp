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

int comp_id = 0;
int comp[N];
stack<int> s;
vi G[N];
vi rG[N];
vi vis(N);
vi scc[N];

void dfs(int u)
{
    if (vis[u]) return;
    vis[u] = 1;

    for (auto v : G[u]) {
        dfs(v);
    }

    s.push(u);
}

void dfs2(int u)
{
    if (vis[u]) return;
    vis[u] = 1;
    comp[u] = comp_id;
    scc[comp_id].push_back(u);

    for (auto v : rG[u]) {
        dfs2(v);
    }
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    while (m--) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        rG[b].push_back(a);
    }

    // Kosaraju's
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        dfs(i);
    }

    dbg(s);

    fill(all(vis), 0);
    while (s.size()) {
        int u = s.top();
        s.pop();
        if (vis[u]) continue;
        dfs2(u);
        comp_id++;
    }

    dbg(comp);

    // int u = n, v = -1;
    // for (int i = n - 1; i > 0; i--) {
    //     if (comp[u] != comp[i]) {
    //         v = i;
    //         break;
    //     }
    // }

    // if (n > 1 && v != -1) {
    //     cout << "NO" << endl;
    //     cout << v << ' ' << u << endl;
    // } else {
    //     cout << "YES" << endl;
    // }

    if (comp_id == 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
        cout << scc[0][0] << ' ' << scc[1][0];
    }

    return 0;
}