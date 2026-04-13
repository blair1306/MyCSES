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

class MergeSegmentTree {
public:
  MergeSegmentTree(const vi& arr) : n(arr.size()), offset(4 * n + 1)
  {
    vi sizes(4 * n + 1, 0);
    computeSizes(sizes, 1, 0, n - 1);

    offset[0] = 0;
    for (int i = 1; i <= 4 * n; i++) {
      offset[i] = offset[i - 1] + sizes[i - 1];
    }
    tree.resize(offset[4 * n]);

    build(arr, 1, 0, n - 1);
  }

  int query(int l, int r, int a, int b)
  {
    return query(1, 0, n - 1, l, r, a, b);
  }

  int n;
  vi offset;
  vi tree;

private:
  int* begin(int at)
  {
    return &tree[offset[at]];
  }

  int* end(int at)
  {
    return &tree[offset[at + 1]];
  }

  int size(int at)
  {
    return offset[at + 1] - offset[at];
  }

  void computeSizes(vi& sizes, int at, int al, int ar)
  {
    sizes[at] = ar - al + 1;
    if (ar == al) return;

    int mid = (al + ar) / 2;
    computeSizes(sizes, 2 * at, al, mid);
    computeSizes(sizes, 2 * at + 1, mid + 1, ar);
  }

  int query(int at, int al, int ar, int l, int r, int a, int b)
  {
    if (r < al || ar < l) return 0;
    if (l <= al && ar <= r) {
      return upper_bound(begin(at), end(at), b) - lower_bound(begin(at), end(at), a);
    }

    int mid = (al + ar) / 2;
    int lAns = query(2 * at, al, mid, l, r, a, b);
    int rAns = query(2 * at + 1, mid + 1, ar, l, r, a, b);

    return lAns + rAns;
  }

  void build(const vi& arr, int at, int al, int ar)
  {
    if (al == ar) {
      tree[offset[at]] = arr[al];
      return;
    }

    int mid = (al + ar) / 2;
    build(arr, 2 * at, al, mid);
    build(arr, 2 * at + 1, mid + 1, ar);

    merge(begin(2 * at), end(2 * at), begin(2 * at + 1), end(2 * at + 1), begin(at));
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vi nums(n);
  for (int i = 0; i < n; i++) cin >> nums[i];

  MergeSegmentTree segtree(nums);
  dbg(segtree.tree);
  while (q--) {
    int l, r, a, b;
    cin >> l >> r >> a >> b;
    l--, r--;
    cout << segtree.query(l, r, a, b) << endl;
  }

  return 0;
}