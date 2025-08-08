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

int n;

vi g[N];
int cap[N][N];
int flow[N][N];
vi parent(N);

int bfs()
{
    parent.assign(N, 0);
    queue<int> q;
    q.push(1);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (parent[v] || flow[u][v] <= 0) continue;
            parent[v] = u;
            q.push(v);
        }
    }

    return parent[n];
}

int edmondsKarp()
{
    int maxFlow = 0;
    while (bfs()) {
        int u = n, v;
        while (u != 1) {
            v = u;
            u = parent[u];
            flow[u][v] -= 1;
            flow[v][u] += 1;
        }
        maxFlow++;
    }

    return maxFlow;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m;
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        cap[a][b] = 1;
        flow[a][b] = 1;
    }

    int days = edmondsKarp();
    cout << days << endl;

    for (int u : g[1]) {
        if (flow[1][u] > 0 || cap[1][u] <= 0) continue;
        vi aug;
        aug.push_back(1);
        aug.push_back(u);
        int back = aug.back();
        while (back != n) {
            for (int v : g[back]) {
                if (flow[back][v] > 0 || cap[back][v] <= 0) continue;
                aug.push_back(v);
                back = v;
                break;
            }
        }
        cout << aug.size() << endl;
        for (int i : aug) cout << i << " ";
        cout << endl;
    }

    return 0;
}