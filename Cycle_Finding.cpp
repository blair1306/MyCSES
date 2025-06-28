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

using Edge = vector<tuple<int, int, ll>>;
using Graph = vector<vector<pair<int, ll>>>;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    Edge E;
    Graph G(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        E.push_back({a, b, c});
        G[a].push_back({b, c});
    }

    vll dis(n + 1, 0);  // set all distances to 0 to detect cycles even unreachable from 1;
    vi parent(n + 1, 0);
    dis[1] = 0;
    int cycle_start = 0;
    for (int i = 1; i <= n; i++) {  // n times to detect cycle
        cycle_start = 0;
        for (auto &[u, v, w] : E) {
            if (dis[v] > dis[u] + w) {
                parent[v] = u;
                dis[v] = dis[u] + w;
                cycle_start = u;
            }
        }
    }

    dbg(cycle_start, parent, dis);

    if (cycle_start == 0) {
        cout << "NO" << endl;
        return 0;
    }

    for (int i = 0; i < n; i++)
        cycle_start = parent[cycle_start];  // this make sure cycle_start is in the cycle

    vi cycle;
    unordered_set<int> s;
    int tmp = cycle_start;
    while (s.find(cycle_start) == s.end()) {
        s.insert(cycle_start);
        cycle.push_back(cycle_start);
        cycle_start = parent[cycle_start];
    }
    reverse(all(cycle));
    cout << "YES" << endl;
    cout << tmp << ' ';
    for (auto a : cycle) {
        cout << a << ' ';
    }
    cout << endl;

    return 0;
}