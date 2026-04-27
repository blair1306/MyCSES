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

struct BIT2D {
  vvi bit;
  explicit BIT2D(int n, int m) : bit(n + 1, vi(m + 1))  // row, col
  {
  }

  void add(int r, int c, int v)
  {
    for (; r < bit.size(); r += r & -r) {
      for (int x = c; x < bit[0].size(); x += x & -x) {
        bit[r][x] += v;
      }
    }
  }

  int query(int r, int c)
  {
    int ans = 0;
    for (; r > 0; r -= r & -r) {
      for (int x = c; x > 0; x -= x & -x) {
        ans += bit[r][x];
      }
    }

    return ans;
  }

  int query(int r1, int c1, int r2, int c2)
  {
    // inclusion-exclusion..
    return query(r2, c2) - query(r2, c1 - 1) - query(r1 - 1, c2) + query(r1 - 1, c1 - 1);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  BIT2D bit(n, n);
  vvi forest(n + 1, vi(n + 1));
  for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= n; c++) {
      char s;
      cin >> s;
      if (s == '*') {
        bit.add(r, c, 1);
        forest[r][c] = 1;
      }
    }
  }

  dbg(forest);
  dbg(bit.bit);

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int y, x;
      cin >> y >> x;
      if (forest[y][x] == 0) {
        forest[y][x] = 1;
        bit.add(y, x, 1);
      } else {
        forest[y][x] = 0;
        bit.add(y, x, -1);
      }
    } else {
      int y1, x1, y2, x2;
      cin >> y1 >> x1 >> y2 >> x2;
      cout << bit.query(y1, x1, y2, x2) << endl;
    }
  }

  return 0;
}