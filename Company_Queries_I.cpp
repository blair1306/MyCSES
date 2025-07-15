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

const int level = 32;
int nxt[level][N];

int binaryLift(int x, int k)
{
    for (int i = 0; i < level; i++) {
        if (x == -1) return x;
        if ((1 << i) & k) x = nxt[i][x];
    }

    return x;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    nxt[0][1] = -1;
    for (int i = 2; i <= n; i++) {
        cin >> nxt[0][i];
    }

    for (int i = 1; i < level; i++) {
        for (int e = 1; e <= n; e++) {
            if (nxt[i - 1][e] == -1)
                nxt[i][e] = -1;
            else
                nxt[i][e] = nxt[i - 1][nxt[i - 1][e]];
        }
    }

    dbg(nxt);
    while (q--) {
        int x, k;
        cin >> x >> k;
        cout << binaryLift(x, k) << endl;
    }

    return 0;
}