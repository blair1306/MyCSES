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

int nxt[N];
int sz[N];

int find(int u)
{
    if (u == nxt[u]) return u;
    nxt[u] = find(nxt[u]);
    return nxt[u];
}

int unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (sz[a] < sz[b]) swap(a, b);
    nxt[b] = a;
    sz[a] += sz[b];
    return sz[a];
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        nxt[i] = i;
        sz[i] = 1;
    }

    int biggest_sz = 1;
    int n_comp = n;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        int sz_comp = 0;
        if (find(a) != find(b)) {
            n_comp--;
            sz_comp = unite(a, b);
            biggest_sz = max(biggest_sz, sz_comp);
        }
        cout << n_comp << ' ' << biggest_sz << endl;
    }

    dbg(sz);

    return 0;
}