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

    int n; // num of pupils
    int m; // num of friendships;
    bool possible = true;

    cin >> n >> m;
    vi color(n + 1);
    vvi graph(n + 1, vi());

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int num_visited = 0;
    queue<int> que;

    while (possible && (!que.empty() || (num_visited < n)))
    {
        if (que.empty())
        {
            for (int i = 1; i <= n; i++)
            {
                if (color[i] == 0)
                {
                    num_visited++;
                    color[i] = 1;
                    que.push(i);
                    break;
                }
            }
        }

        while (!que.empty())
        {
            int a;
            int nc;
            a = que.front();
            que.pop();
            nc = (color[a] == 1 ? 2 : 1);
            for (int b : graph[a])
            {
                if (color[b] == color[a])
                {
                    possible = false;
                }
                if (color[b] == 0)
                {
                    color[b] = nc;
                    num_visited++;
                    que.push(b);
                }
            }
        }
    }

    if (!possible)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            cout << color[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}