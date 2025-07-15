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

int kd_id = 0;
vi vis(N);
vi G[N];
vi rG[N];
vi kid(N);
stack<int> S;

void dfs(int u)
{
    if (vis[u]) return;
    vis[u] = 1;
    for (auto v : G[u]) {
        dfs(v);
    }

    S.push(u);
}

void rdfs(int u)
{
    if (vis[u]) return;
    vis[u] = 1;
    kid[u] = kd_id;
    for (auto v : rG[u]) {
        rdfs(v);
    }
}

void Kosaraju(int n)
{
    fill(all(vis), 0);
    for (int i = 1; i <= n; i++) {
        dfs(i);
    }

    fill(all(vis), 0);
    while (S.size()) {
        int u = S.top();
        S.pop();
        if (vis[u]) continue;
        kd_id++;
        rdfs(u);
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
    Kosaraju(n);
    dbg(vis);
    dbg(kid);

    cout << kd_id << endl;
    for (int i = 1; i <= n; i++) {
        cout << kid[i] << ' ';
    }
    cout << endl;

    return 0;
}