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
vi pre(N, 0);
vi state(N, 0);
vi cycle;

bool dfs(int u)
{
    state[u] = 1;
    for (auto v : G[u]) {
        if (state[v] == 0) {
            pre[v] = u;
            if (dfs(v)) return true;
        } else if (state[v] == 1) {
            cycle.push_back(v);
            for (int x = u; x != v; x = pre[x]) {
                // since pre[v] = u so we start from u
                cycle.push_back(x);
            }
            cycle.push_back(v);
            reverse(cycle.begin(), cycle.end());
            return true;
        }
    }

    state[u] = 2;
    return false;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    bool hasCycle = false;
    for (int i = 1; i <= n; i++) {
        if (state[i] != 0) continue;
        hasCycle = dfs(i);
        if (hasCycle) break;
    }

    if (!hasCycle) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    dbg(pre);

    cout << cycle.size() << endl;
    for (int u : cycle) cout << u << ' ';
    cout << endl;
    return 0;
}