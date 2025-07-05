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
const int N = 1e5 + 5;  // size for global arrays (if needed)
#endif

vi G[N];
vi state(N, 0);
vi dist(N, INF);
vi pre(N, 0);

void dfs2(int u)
{
    for (auto v : G[u]) {
        if (state[v] == 0 || state[v] == 1) continue;
        if (dist[u] + 1 > dist[v]) {
            dist[v] = dist[u] + 1;
            dfs2(v);
            pre[v] = u;
        }
    }
}

void dfs(int u)
{
    state[u] = 1;

    for (auto v : G[u]) {
        if (state[v] == 0) {
            dist[v] = dist[u] + 1;
            pre[v] = u;
            dfs(v);
        }
        if (state[v] == 2) {
            if (dist[u] + 1 > dist[v]) {
                dist[v] = dist[u] + 1;
                pre[v] = u;
                dfs2(v);
            }
        }
    }

    state[u] = 2;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    state.resize(n + 1);
    dist.resize(n + 1);
    pre.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    dist[1] = 0;

    dfs(1);

    if (dist[n] == INF) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    dbg(dist);
    dbg(pre);
    vi longest_flight;
    int s = n;
    while (s != 0) {
        longest_flight.push_back(s);
        s = pre[s];
    }
    reverse(all(longest_flight));

    dbg(longest_flight);
    cout << longest_flight.size() << endl;
    for (int u : longest_flight) cout << u << ' ';
    cout << endl;

    return 0;
}