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
const int N = 5;   // size for global arrays (if needed)
#else
const int N = 500+1;   // size for global arrays (if needed)
#endif


int dp[N][N];


int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int a, b;
    cin >> a >> b;

    for(int i = 1; i <= a; i++)
    {
        for(int j = 1; j <= b; j++)
        {
            dp[i][j] = INF;
        }
    }

    for(int i = 1; i <= a; i++)
    {
        for(int j = 1; j <= b; j++)
        {
            if(i == j) { dp[i][j] = 0; continue; }
            for(int k = 1; j-k>0; k++)
            {
                dp[i][j] = min(dp[i][j-k] + dp[i][k] + 1, dp[i][j]);
            }
            for(int k = 1; i-k>0; k++)
            {
                dp[i][j] = min(dp[i-k][j] + dp[k][j] + 1, dp[i][j]);
            }
        }
    }

    dbg(dp);

    cout << dp[a][b] << endl;

    return 0;
}