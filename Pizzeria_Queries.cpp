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

template <typename T>
struct SegTree {
  int n;
  vector<T> tree;
  T ID = 0;

  SegTree(int _n) : n(_n), tree(4 * _n, ID)
  {
  }

  T combine(T a, T b)
  {
    return max(a, b);
  }

  void update(int v, int tl, int tr, int pos, T new_val)
  {
    if (tl == tr) {
      tree[v] = new_val;
      return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      update(2 * v, tl, tm, pos, new_val);
    else
      update(2 * v + 1, tm + 1, tr, pos, new_val);
    tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
  }

  void update(int k, T new_val)
  {
    return update(1, 0, n - 1, k, new_val);
  }

  T query(int v, int tl, int tr, int l, int r)
  {
    if (l > r) return ID;
    if (l == tl && r == tr) return tree[v];
    int tm = (tl + tr) / 2;
    return combine(query(2 * v, tl, tm, l, min(r, tm)),
                   query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  T query(int l, int r)
  {
    return query(1, 0, n - 1, l, r);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  SegTree<ll> segL(n), segR(n);
  for (int i = 0; i < n; i++) {
    ll p;
    cin >> p;
    segL.update(i, p - i - 1);
    segR.update(i, p + i + 1);
  }

  while (q--) {
    int t, k;
    cin >> t;
    if (t == 1) {
      int x;
      cin >> k >> x;
      segL.update(k - 1, x - k);
      segR.update(k - 1, x + k);
    } else {
      cin >> k;
      cout << max(segL.query(0, k - 1) + k, segR.query(k, n - 1) - k) << endl;
    }
  }

  return 0;
}