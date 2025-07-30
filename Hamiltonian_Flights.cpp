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
const int N = 4;  // size for global arrays (if needed)
#else
const int N = 20;  // size for global arrays (if needed)
#endif

vi rG[N];
int dp[1 << N][N];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        rG[--b].push_back(--a);
    }

    dp[1][0] = 1;
    for (int submask = 2; submask < (1 << n); submask++) {
        if (!(submask & 1)) continue;

        for (int v = 1; v < n; v++) {
            for (auto u : rG[v]) {
                if (!(submask & (1 << (v)))) continue;
                if (submask == (1 << n) - 1 && v != n - 1) continue;
                int premask = submask ^ (1 << (v));
                dp[submask][v] = (dp[premask][u] + dp[submask][v]) % MOD;
            }
        }
    }

    dbg(dp);
    cout << dp[(1 << n) - 1][n - 1] << endl;

    return 0;
}