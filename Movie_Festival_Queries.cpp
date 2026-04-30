#if defined(__has_include) && __has_include(<bits/stdc++.h>)
#include <bits/stdc++.h>
#else
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
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
#define sz(x) (x).size()

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

#ifdef LOCAL
const int MAXT = 11 + 1;
const int LOG = 20;

#else
const int MAXT = 1e6 + 1;
const int LOG = 20;
#endif

int up[MAXT][LOG];  // jump backwards from leaving time

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vi best(MAXT, 0);  // latest start for any movie that ends <= t;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    best[b] = max(best[b], a);
  }

  // propagate so that t's value won't be 0 even if no movie ends at t
  for (int t = 1; t < MAXT; t++) {
    best[t] = max(best[t], best[t - 1]);
  }

  // build the binary lift table
  for (int t = 1; t < MAXT; t++) {
    up[t][0] = best[t];
  }

  for (int l = 1; l < LOG; l++) {
    for (int t = 1; t < MAXT; t++) {
      /*
      up[t][l] = take 2^l steps back from t
      First half: take 2^(l-1) steps back from t → lands at up[t][l-1]
      Second half: take 2^(l-1) more steps from there
      */
      up[t][l] = up[up[t][l - 1]][l - 1];
    }
  }

  dbg(best);
  dbg(up);

  while (q--) {
    int a, b;
    cin >> a >> b;

    int ans = 0;
    int t = b;
    for (int l = LOG - 1; l >= 0; l--) {
      if (up[t][l] >= a) {
        t = up[t][l];
        ans += (1 << l);
      }
    }

    cout << ans << endl;
  }

  return 0;
}