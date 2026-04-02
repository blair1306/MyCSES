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

struct Fenwick {
  vll bit;
  Fenwick(int n) : bit(n + 1, 0)
  {
  }

  void range_set(int l, int r, int dt)
  {
    set(r + 1, -dt);
    set(l, dt);
  }

  void set(int k, int dt)
  {
    k += 1;
    for (; k < bit.size(); k += k & -k) {
      bit[k] += dt;
    }
  }

  ll query(int k)
  {
    ll ans = 0;
    k += 1;
    for (; k > 0; k -= k & -k) {
      ans += bit[k];
    }

    return ans;
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vll dt(n);
  Fenwick fenw(n);
  ll sum = 0;
  /*
  dt[i] + sum(0..i-1) = sum = k
  */
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    dt[i] = x - sum;
    sum += dt[i];
    fenw.set(i, dt[i]);
  }

  dbg(dt);

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int a, b, u;
      cin >> a >> b >> u;
      a--, b--;
      fenw.range_set(a, b, u);
    } else {
      int k;
      cin >> k;
      k--;
      cout << fenw.query(k) << endl;
    }
  }

  return 0;
}