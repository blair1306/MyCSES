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

using Edge = pair<ll, int>;
vector<Edge> G[N];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    int k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        G[a].push_back({c, b});
    }

    vector<vll> dist(n + 1);
    priority_queue<Edge> q;
    q.push({0, 1});
    while (!q.empty()) {
        auto [uw, u] = q.top();
        uw = -uw;
        q.pop();
        dbg(dist);
        if (dist[u].size() >= k) continue;
        dist[u].push_back(uw);
        for (auto [vw, v] : G[u]) {
            ll nw = uw + vw;
            if (dist[v].size() < k) {
                q.push({-nw, v});
            }
        }
    }

    for (auto i : dist[n]) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}