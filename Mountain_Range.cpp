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

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    vi mts(n);
    for (int i = 0; i < n; i++) cin >> mts[i];

    int max_len = 0;
    for (int rev = 0; rev <= 1; rev++) {
        int max_height = 0;
        int len = 0;
        if (rev) reverse(all(mts));
        for (int i = 0; i < n; i++) {
            if (mts[i] >= max_height) {
                max_height = mts[i];
                len = 0;
            } else {
                len++;
                max_len = max(len, max_len);
            }
        }
    }

    cout << max_len << endl;

    return 0;
}