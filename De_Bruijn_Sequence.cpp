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

vi dbrjSeq;
vector<vector<pii>> G;
int cnt = 0;
vi vis;
vi val;

void dfs(int u)
{
    while (G[u].size()) {
        auto [v, eid] = G[u].back();
        G[u].pop_back();
        if (vis[eid]) continue;
        vis[eid] = 1;
        dfs(v);
    }

    dbrjSeq.push_back(u);
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    if (n == 1) {
        cout << "01" << endl;
        return 0;
    }
    n--;
    int bitmask = static_cast<int>(pow(2, n)) - 1;
    int eSize = static_cast<int>(pow(2, n + 1));
    G.resize(bitmask + 1);
    vis.resize(eSize + 1);
    val.resize(eSize + 1);

    for (int i = 0; i <= bitmask; i++) {
        G[i].push_back({(i << 1) & bitmask, cnt++});
        G[i].push_back({((i << 1) + 1) & bitmask, cnt++});
    }

    dbg(G);
    dfs(0);
    dbg(dbrjSeq);
    dbrjSeq.pop_back();
    reverse(all(dbrjSeq));

    while (n--) cout << 0;
    for (auto s : dbrjSeq) {
        if (s % 2 == 0)
            cout << 0;
        else
            cout << 1;
    }
    cout << endl;

    return 0;
}