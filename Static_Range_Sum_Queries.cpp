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

    int n, q;
    cin >> n >> q;
    vll prefixSum(n + 1);
    vi num(n + 1);
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
        prefixSum[i] = sum;
        num[i] = x;
    }

    dbg(prefixSum);

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << prefixSum[b] - prefixSum[a - 1] << endl;
    }

    return 0;
}