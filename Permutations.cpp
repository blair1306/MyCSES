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

    // 5 5 3 1 4 2
    // 135 24 1 3 5 2 4
    // 4 2 4 1 3
    // 4 1 2 3 4 ->1 2 | 1 3 2 4
    int n;
    cin >> n;
    if (n <= 3 && n > 1) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    int i;
    for (i = 2; i <= n; i += 2) cout << i << " ";
    for (i = 1; i <= n; i += 2) cout << i << " ";

    return 0;
}