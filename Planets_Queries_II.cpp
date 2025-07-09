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
const int N = 5 + 1;  // size for global arrays (if needed)
#else
const int N = 2e5 + 5;  // size for global arrays (if needed)
#endif

const int level = 31;

int nxt[level][N];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nxt[0][i];
    }

    for (int i = 1; i < level; i++) {
        for (int j = 1; j <= n; j++) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        }
    }

    dbg(nxt);

    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        if (a == b) {
            cout << 0 << endl;
            continue;
        }
        for (int i = 0; i < level; i++) {
            if (nxt[i][a] == b) {
                ans = 1;
                while (i--) {
                    ans *= 2;
                }
                cout << ans << endl;
                break;
            }
        }
        if (!ans) cout << -1 << endl;
    }

    return 0;
}