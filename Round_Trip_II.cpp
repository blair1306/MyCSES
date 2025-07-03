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

vector<pii> E;
vi pre(N, 0);
vi visited(N, 0);
vi dist(N, 0);

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    pre.resize(n + 1);
    visited.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        E.push_back({a, b});
    }

    bool hasLoop;
    int loopStart = 0;
    for (int i = 0; i < n; i++) {
        hasLoop = false;
        for (auto [u, v] : E) {
            int nw = dist[u] - 1;
            if (nw < dist[v]) {
                pre[v] = u;
                dist[v] = nw;
                hasLoop = true;
                loopStart = u;
            }
        }
    }

    dbg(pre);
    dbg(dist);

    if (!hasLoop) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        loopStart = pre[loopStart];
    }

    vi roundTrip;
    roundTrip.push_back(loopStart);
    while (loopStart != roundTrip[0] || roundTrip.size() < 2) {
        loopStart = pre[loopStart];
        roundTrip.push_back(loopStart);
    }

    reverse(roundTrip.begin(), roundTrip.end());
    cout << roundTrip.size() << endl;
    for (int u : roundTrip) {
        cout << u << ' ';
    }
    cout << endl;

    return 0;
}