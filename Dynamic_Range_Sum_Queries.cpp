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

template <class T>
class RSQ {
  using Arr = vector<T>;

private:
  T DEFAULT = 0;
  int sz;
  Arr segtree;

  T sum(const T& a, const T& b)
  {
    return a + b;
  }

  void build(const Arr& arr, int at, int at_left, int at_right)
  {
    if (at_left == at_right) {
      segtree[at] = arr[at_left];
      return;
    }
    int mid = (at_left + at_right) / 2;
    build(arr, at * 2, at_left, mid);
    build(arr, at * 2 + 1, mid + 1, at_right);
    segtree[at] = sum(segtree[at * 2], segtree[at * 2 + 1]);
  }

  void set(int at, int idx, T val, int at_left, int at_right)
  {
    if (at_left == at_right) {
      segtree[at] = val;
      return;
    }
    int mid = (at_left + at_right) / 2;
    if (idx <= mid) {
      set(at * 2, idx, val, at_left, mid);
    } else {
      set(at * 2 + 1, idx, val, mid + 1, at_right);
    }
    segtree[at] = sum(segtree[at * 2], segtree[at * 2 + 1]);
  }

  T query(int start, int end, int at, int at_left, int at_right)
  {
    if (start > at_right || end < at_left) return DEFAULT;
    // the queried range is fully covered by the node's range
    // [start [at_left, at_right] end]
    if (start <= at_left && end >= at_right) return segtree[at];
    int mid = (at_left + at_right) / 2;
    T left_res = query(start, end, at * 2, at_left, mid);
    T right_res = query(start, end, at * 2 + 1, mid + 1, at_right);
    return sum(left_res, right_res);
  }

public:
  RSQ(const Arr& arr)
  {
    /*
    Capacity: segtree is allocated as sz * 4 (≈ 4·n) — the buffer/capacity for tree nodes.
    Range: logical array range used for build/query/set is [0, sz-1] where sz == arr.size().
    */
    sz = arr.size();
    segtree = Arr(sz * 4, DEFAULT);
    build(arr, 1, 0, sz - 1);
    dbg("built");
    dbg(segtree);
  }

  void set(int idx, T val)
  {
    set(1, idx, val, 0, sz - 1);
    dbg(segtree);
  }

  T query(int start, int end)
  {
    return query(start, end, 1, 0, sz - 1);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;
  vll arr(n, 0);
  for (int i = 0; i < n; i++) cin >> arr[i];

  dbg(arr);

  RSQ<ll> rsq(arr);

  while (q--) {
    int k, a, b;
    ll u;
    int t;
    cin >> t;
    if (t == 1) {
      cin >> k >> u;
      rsq.set(k - 1, u);
    } else {
      cin >> a >> b;
      cout << rsq.query(a - 1, b - 1) << endl;
    }
  }
  return 0;
}