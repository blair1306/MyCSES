#if defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#endif

// #define LOCAL
#ifdef LOCAL
#include "mydebug.h"
#else
#define dbg(...)
#define dbg_arr(...)
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

// Constants
const int INF = 1e9 + 5;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; // or 998244353
const int N = 1e5 + 1;   // size for global arrays (if needed)

bool visited[N];
int parent[N];
int cycle_s = -1;
int cycle_e = -1;
vi graph[N];

bool dfs(int u, int p)
{
    // skip parent to avoid trivial cycles
    visited[u] = true;
    for (int v : graph[u])
    {
        if (v == p)
            continue; // skip parent
        if (visited[v])
        {
            cycle_e = v;
            cycle_s = u;
            return true;
        }
        parent[v] = u;
        if (dfs(v, u))
            return true;
    }

    return false;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (visited[i])
            continue;
        parent[i] = -1;
        if (dfs(i, -1))
        {
            vi cycle;
            cycle.push_back(cycle_e);
            int u = cycle_s;
            while (u != cycle_e)
            {
                dbg(cycle_s, cycle_e, u, cycle);
                cycle.push_back(u);
                u = parent[u];
            }
            cycle.push_back(cycle_e);
            reverse(all(cycle));
            cout << cycle.size() << endl;
            for (int c : cycle)
            {
                cout << c << ' ';
            }
            cout << endl;
            return 0;
        }
    }

    cout << "IMPOSSIBLE" << endl;

    return 0;
}