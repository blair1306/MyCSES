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
typedef vector<pii> vpii;

// Shortcuts
#define endl '\n'
#define all(x) (x).begin(), (x).end()

// Constants
const int INF = 1e9 + 5;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; // or 998244353
#ifdef LOCAL
const int N = 10 + 1; // size for global arrays (if needed)
#else
const int N = 1e5 + 1; // size for global arrays (if needed)
#endif

int plink[N];

int find(int i) // flatten the whole thing
{
    if (i == plink[i])
        return i;

    return plink[i] = find(plink[i]);
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);

    plink[a] = b;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int k;
    int n; // num of cities
    int m; // num of roads
    vpii nw_roads;
    int a, b;

    cin >> n >> m;

    for (int i = 0; i < N; i++)
        plink[i] = i;

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        dbg(a, b);
        if (find(a) != find(b))
        {
            dbg(plink[a], plink[b]);
            unite(a, b);
            dbg(plink[a], plink[b]);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        find(i);
    }
    sort(plink + 1, plink + n + 1);

    int last = plink[1];

    for (int i = 2; i <= n; i++)
    {
        if (plink[i] != last)
        {
            nw_roads.push_back({last, plink[i]});
            last = plink[i];
        }
    }

    k = nw_roads.size();
    cout << k << endl;
    if (k)
    {
        for (auto p : nw_roads)
            cout << p.first << " " << p.second << endl;
    }

    return 0;
}