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
const int N = 2e5 + 5;   // size for global arrays (if needed)

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // num of nodes
    int m; // num of connections

    cin >> n >> m;

    vvi graph(n + 1, vi());
    vi visited(n + 1, 0);
    vi parent(n + 1, -1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int k = 0;
    queue<int> q;
    q.push(1);
    visited[1] = 1;
    bool found = false;
    vi distance(n + 1, 0);

    while (!q.empty() && !found)
    {
        int qsize = q.size();
        for (int i = 0; i < qsize; i++)
        {
            int a = q.front();
            q.pop();
            distance[a] = k;
            if (a == n)
            {
                found = true;
                break;
            }
            for (auto b : graph[a])
            {
                if (visited[b])
                    continue;
                visited[b] = true; // mark as visited here!!!
                parent[b] = a;
                q.push(b);
            }
        }
        k++;
    }

    vi route;
    if (!found)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        while (n != -1)
        {
            route.push_back(n);
            n = parent[n];
        }

        reverse(route.begin(), route.end());
        k = route.size();
        cout << k << endl;
        for (auto i : route)
        {
            cout << i << " ";
        }

        cout << endl;
    }

    return 0;
}