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
#ifdef LOCAL
const int N = 10+1;   // size for global arrays (if needed)
#else
const int N = 500+1;   // size for global arrays (if needed)
#endif

ll graph[N][N];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int i, j;
    int n, m, q;
    cin >> n >> m >> q;

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            graph[i][j] = LINF;
        graph[i][i] = 0;        // i to i is 0!
    }

    for(i = 0; i < m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        graph[u][v] = graph[v][u] = min(graph[u][v],w);
    }

    // Floyd Warshal?
    for(int k = 1; k <= n; k++)  // for every k as intermidiary!!!
    {
       for(int u = 1; u <= n; u++)
        {
            for(int v = 1; v <= n; v++)
            {
                graph[u][v] = min(graph[u][v], graph[u][k]+graph[k][v]);
            }
        }
    }

    dbg(graph);

    for(i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        ll w = graph[u][v];
        if(w == LINF)
            cout << -1 << endl;
        else
            cout << graph[u][v] << endl;
    }

    return 0;
}