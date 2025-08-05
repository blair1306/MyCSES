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
const int N = 500 + 5;  // size for global arrays (if needed)
#endif

vi graph[N];
ll capacity[N][N];
vi parent(N);
int n;

bool reachable()
{
    fill(all(parent), 0);
    queue<int> q;
    q.push(1);
    // bfs
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto v : graph[u]) {
            if (parent[v] || capacity[u][v] <= 0) continue;
            q.push(v);
            parent[v] = u;
        }
    }

    return parent[n];
}

ll maxFlow()
{
    ll ans = 0;
    while (reachable()) {
        ll currFlow = LINF;
        dbg(parent);
        int v, u = n;
        while (u != 1) {
            v = u;
            u = parent[u];
            dbg(u, v);
            currFlow = min(currFlow, capacity[u][v]);
        }

        dbg(currFlow);
        if (currFlow == 0) break;
        ans += currFlow;
        u = n;
        while (u != 1) {
            v = u;
            u = parent[u];
            capacity[u][v] -= currFlow;
            capacity[v][u] += currFlow;
        }
    }

    return ans;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m;
    ll ans = 0;
    cin >> n >> m;

    while (m--) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        graph[a].push_back(b);
        /*
        For any edge u → v, the residual capacity is:

        capacity[u][v] - flow[u][v]

        But we also define a reverse edge v → u, whose residual capacity is:

        flow[u][v]

        This reverse edge allows the algorithm to send flow backward to adjust a previously chosen
        path.*/
        graph[b].push_back(a);
        capacity[a][b] += c;
    }

    // Edmonds-Karp
    ans = maxFlow();

    cout << ans << endl;

    return 0;
}