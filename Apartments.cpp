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

    int n, m;
    int k;
    cin >> n >> m >> k;
    vi applicant(n);
    vi appartment(m);

    for (int i = 0; i < n; i++) {
        cin >> applicant[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> appartment[i];
    }

    sort(applicant.begin(), applicant.end());
    sort(appartment.begin(), appartment.end());
    int i = 0;
    int j = 0;
    int match = 0;
    while (i < n && j < m) {
        int too_big = applicant[i] < appartment[j] - k;
        int too_small = applicant[i] > appartment[j] + k;
        if (!too_big && !too_small) {
            match++;
            i++;
            j++;
        } else if (too_big)
            i++;
        else
            j++;
    }

    cout << match << endl;

    return 0;
}