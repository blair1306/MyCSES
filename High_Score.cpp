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
const int MOD = 1e9 + 7; // or 998244353
#ifdef LOCAL
const int N = 10+1;   // size for global arrays (if needed)
#else
const int N = 2500+1;   // size for global arrays (if needed)
#endif

ll dist[N];
int visited_n[N];
int visited_0[N];
int inloop[N];
vi rev_graph[N];
vi graph[N];

typedef tuple<int, int, int> edge;
typedef vector<edge> edge_list;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    edge_list edg;

    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++)
    {
        dist[i] = LINF;
    }

    for(int i = 0; i < m; i++)
    {
        int a, b, x;
        cin >> a >> b >> x;
        edg.push_back({a, b, -x});
        rev_graph[b].push_back(a);
        graph[a].push_back(b);
    }

    // initial condition
    dist[1] = 0;
    for(int i = 1; i < n; i++)      // n-1 rounds ! and why?
    for(auto [u, v, w]: edg)
    {
        // if(i != u) continue;
        if(dist[u]+w < dist[v])
        {
            dist[v] = dist[u]+w;
        }
    }

    bool has_loop = false;
    for(auto [u, v, w]: edg)
    {
        if(dist[u]+w < dist[v])
        {
            has_loop = true;
            inloop[u] = 1;
            inloop[v] = 1;
        }
    }

    dbg(inloop);

    // yes even if there's a loop, but we can't use it if it's not in our path!!!
    // and we reverse the graph and try to reach marked node from n with dfs

    // and "apparently" we need to check if the node in the loop is reachable from 1 as well
    queue<int> q;
    q.push(1);

    while(has_loop && !q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v: graph[u])
        {
            if(visited_0[v]) continue;
            visited_0[v] = 1;

            q.push(v);
        }
    }

    q.push(n);

    while(has_loop && !q.empty())
    {
        int u = q.front();
        q.pop();
        if(inloop[u] && visited_0[u])
        {
            cout << -1 << endl;
            return 0;
        }
        for(int v: rev_graph[u])
        {
            if(visited_n[v]) continue;
            visited_n[v] = 1;

            dbg(v);
            q.push(v);
        }
    }

    
    cout << -dist[n] << endl;


    return 0;
}