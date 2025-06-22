#if defined(__APPLE__)
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

#elif defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else

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
const int N = 2e5 + 5;   // size for global arrays (if needed)

// Debugging (remove for submission)
#define DEBUG 0
#define dbg(x) \
    if (DEBUG) \
        cerr << #x << " = " << x << endl;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    return 0;
}