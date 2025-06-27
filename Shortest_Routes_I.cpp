#if defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#endif

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
const ll LINF = 1e19;
const int MOD = 1e9 + 7; // or 998244353
const int N = 1e5 + 1;   // size for global arrays (if needed)

int n;
int m;

vector<pair<ll, int>> graph[N];
ll dist[N];
int visited[N];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        graph[a].push_back({w, b});
    }

    for(int i = 1; i <= n; i++)
        dist[i] = LINF;
    
    priority_queue<pair<ll, int>> pq;       // -w, v
    pq.push({-1, 1});
    dist[1] = 0;

    while(!pq.empty())
    {
        auto [_, u] = pq.top();
        pq.pop();
        if(visited[u]) continue;
        visited[u] = 1;

        for(auto [w, v]: graph[u])
        {
            ll nw = dist[u] + w;
            if(nw < dist[v])
            {
                dist[v] = nw;
                pq.push({-nw, v});      // -nw instead of -w or else the greedy part fails!!!
            }
        }
    }

    for(int i = 1; i <= n; i++)
    {
        cout << dist[i];
        if(i != n) cout << ' ';
    }

    cout << endl;

    return 0;
}