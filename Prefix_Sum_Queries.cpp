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

struct Node {
  ll sum, maxPref;
};

template <class T>
class SegmentTree {
private:
  // const T DEFAULT = std::numeric_limits<T>().max();
  const T ID = {0, 0};

  int len;
  vector<T> tree;

public:
  explicit SegmentTree(int len) : len(len), tree(len * 2, ID)
  {
  }

  T conquer(T l, T r) const
  {
    return {l.sum + r.sum, max(l.maxPref, l.sum + r.maxPref)};
  }

  void set(int k, T val)
  {
    k += len;
    tree[k] = val;
    for (k /= 2; k >= 1; k /= 2) {
      tree[k] = conquer(tree[2 * k], tree[2 * k + 1]);
    }
  }

  ll range_query(int l, int r)
  {
    T resL = ID, resR = ID;
    for (l += len, r += len; l < r; l /= 2, r /= 2) {
      if (l % 2 == 1) {
        resL = conquer(resL, tree[l++]);
      }
      if (r % 2 == 1) {
        resR = conquer(tree[--r], resR);
      }
    }
    return conquer(resL, resR).maxPref;
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  /*
    1 2 -1 3 1 -5 1 4
    1 2 -1 -2 1 -5 1 4
  */

  int n, q;
  cin >> n >> q;

  SegmentTree<Node> segtree(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    Node node{x, max(0, x)};
    segtree.set(i, node);
  }

  while (q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 1) {
      int k = a, x = b;
      segtree.set(--k, {b, max(0, b)});
    } else {
      cout << segtree.range_query(a - 1, b) << endl;
    }
  }

  return 0;
}