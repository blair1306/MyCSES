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

using Edge = tuple<int, pii>;
vector<Edge> edge;
vvi G[N];
priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

int parent[N];

int find(int a)
{
    if (a == parent[a]) return a;
    return parent[a] = find(parent[a]);
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);

    parent[a] = b;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) parent[i] = i;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edge.push_back({w, {a, b}});
        pq.push({w, {a, b}});
    }

    // Kruskal
    int cnt = 0;
    ll total_weight = 0;
    while (pq.size() && cnt < n) {
        auto [w, e] = pq.top();
        auto [u, v] = e;
        pq.pop();

        if (find(u) == find(v)) continue;  // don't create a cycle
        unite(u, v);
        cnt++;
        total_weight += w;
        dbg(w, u, v);
        dbg(parent);
    }

    dbg(parent);

    if (cnt == n - 1)
        cout << total_weight << endl;
    else
        cout << "IMPOSSIBLE" << endl;

    return 0;
}