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
const int N = 21;  // size for global arrays (if needed)
#else
const int N = 100 * 1000 + 1;  // size for global arrays (if needed)
#endif

vi dp(N, -1);
vi coin(100);
int n;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }

    /*
    You are updating [dp[j + coin[i]]](http://vscodecontentref/0) in the forward direction (j = 0 to
    N-1). This causes you to use "freshly updated" values in the same iteration, which leads to
    overcounting and incorrect results (i.e., using the same coin multiple times in one step).
    */
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < N; j++) {
            if (dp[j] != -1) {
                dp[j + coin[i]] = 1;
            }
        }
    }

    int cnt = 0;
    for (int i = 1; i < N; i++) {
        if (dp[i] != -1) cnt++;
    }
    cout << cnt << endl;
    for (int i = 1; i < N; i++) {
        if (dp[i] != -1) cout << i << ' ';
    }

    cout << endl;

    return 0;
}
