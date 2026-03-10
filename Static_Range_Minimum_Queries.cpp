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
class MinSegmentTree {
public:
  MinSegmentTree(const vector<T>& arr)
  {
    size = arr.size();
    segtree = vector<T>(size * 4, DEFAULT);

    build(arr, 1, 0, size - 1);
  }

  T get_range_min(int start, int end)
  {
    return range_min(start, end, 1, 0, size - 1);
  }

  void set(int idx, const T val, int at, int left, int right)
  {
    if (left == right) {
      segtree[at] = val;
      return;
    }

    int mid = (left + right) / 2;
    if (idx <= mid) {
      set(idx, val, 2 * at, left, mid);
    } else {
      set(idx, val, 2 * at + 1, mid + 1, right);
    }

    segtree[at] = combine(segtree[2 * at], segtree[2 * at + 1]);
  }
#if defined(LOCAL)
  vector<T> segtree;
#endif

private:
  T combine(const T& a, const T& b)
  {
    return std::min(a, b);
  }

  T range_min(int start, int end, int at, int left, int right)
  {
    // no overlap
    if (left > end || right < start) return DEFAULT;
    // fully covered
    if (start <= left && right <= end) return segtree[at];

    int mid = (left + right) / 2;
    T left_res = range_min(start, end, 2 * at, left, mid);
    T right_res = range_min(start, end, 2 * at + 1, mid + 1, right);

    return combine(left_res, right_res);
  }

  void build(const vector<T>& arr, int at, int left, int right)
  {
    if (left == right) {
      segtree[at] = arr[left];
      return;
    }

    int mid = (left + right) / 2;
    build(arr, 2 * at, left, mid);
    build(arr, 2 * at + 1, mid + 1, right);

    segtree[at] = combine(segtree[2 * at], segtree[2 * at + 1]);
  }

  const T DEFAULT = std::numeric_limits<T>().max();
  int size;
#if !defined(LOCAL)
  vector<T> segtree;
#endif
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;
  vi arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];
  MinSegmentTree<int> rmq(arr);
  dbg(rmq.segtree);

  int a, b;
  while (q--) {
    cin >> a >> b;
    a--, b--;
    cout << rmq.get_range_min(a, b) << endl;
  }

  return 0;
}