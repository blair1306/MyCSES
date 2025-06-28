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
const int N = 1e5 + 1;  // size for global arrays (if needed)
#endif

struct Edge {
    int u;
    int v;
    ll w;
};
ll dist[N];
ll disc[N];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    vector<Edge> E;
    int n, m;
    int i;
    cin >> n >> m;
    for (i = 0; i < m; i++) {
        int a, b;
        ll m;
        cin >> a >> b >> m;
        E.push_back({a, b, m});
    }

    for (i = 1; i <= n; i++) {
        dist[i] = LINF;
    }
    dist[1] = 0;
    for (i = 1; i < n; i++)
        for (auto [u, v, w] : E) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    dbg(dist);
    ll ans = LINF;
    for (int i = 0; i < m; i++) {
        for (int i = 1; i <= n; i++) disc[i] = dist[i];
        for (int j = 0; j < m; j++) {
            auto [u, v, w] = E[j];
            if (i == j) w /= 2;
            if (disc[v] > disc[u] + w) {
                disc[v] = disc[u] + w;
            }
        }
        dbg(disc);
        ans = min(ans, disc[n]);
    }

    cout << ans << endl;

    return 0;
}