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

class MaxSegmentTree {
public:
  explicit MaxSegmentTree(const vi& prev) : n(prev.size()), tree(4 * n)
  {
    build(prev, 1, 0, n - 1);
  };

  void update(int k, int v)
  {
    update(1, 0, n - 1, k, v);
  }

  int rangeMax(int l, int r)
  {
    return rangeMax(1, 0, n - 1, l, r);
  }

private:
  int n;
  vi tree;

  void build(const vi& arr, int at, int al, int ar)
  {
    if (al == ar) {
      tree[at] = arr[al];
      return;
    }

    int mid = (al + ar) / 2;
    build(arr, 2 * at, al, mid);
    build(arr, 2 * at + 1, mid + 1, ar);

    tree[at] = max(tree[2 * at], tree[2 * at + 1]);
  }

  void update(int at, int al, int ar, int k, int v)
  {
    if (al == ar) {
      tree[at] = v;
      return;
    }

    int mid = (al + ar) / 2;
    if (k <= mid)
      update(2 * at, al, mid, k, v);
    else
      update(2 * at + 1, mid + 1, ar, k, v);

    tree[at] = max(tree[2 * at], tree[2 * at + 1]);
  }

  int rangeMax(int at, int al, int ar, int l, int r)
  {
    if (ar < l || al > r) return 0;
    if (l <= al && ar <= r) return tree[at];
    int mid = (al + ar) / 2;
    int lMax = rangeMax(2 * at, al, mid, l, r);
    int rMax = rangeMax(2 * at + 1, mid + 1, ar, l, r);

    return max(lMax, rMax);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  unordered_map<int, set<int>> posOfX;
  vi x(n + 1);
  vi prev(n + 1);

  for (int i = 1; i <= n; i++) {
    int xi;
    cin >> xi;
    x[i] = xi;
    auto& pos = posOfX[xi];
    prev[i] = pos.empty() ? 0 : *pos.rbegin();
    pos.insert(i);
  }

  dbg(prev);

  auto get_neighbor = [&](int k, int v) {
    int prev = 0, next = 0;
    auto& S = posOfX[v];
    auto it = S.find(k);
    /*
    set: { 2, 5, 8, 11 }
           ↑              ↑
        begin()          end()   ← points to "nothing", one past 8

        *begin() == 2   ✅
        *end()          ❌ UB — dereferencing end() is always undefined behavior*/
    if (it != S.begin()) prev = *(std::prev(it));
    if (std::next(it) != S.end()) next = *(std::next(it));

    return make_pair(prev, next);
  };

  MaxSegmentTree segtree(prev);

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int k, u;
      cin >> k >> u;
      // update old next to old prev, then update new prev
      int oldX = x[k];
      if (oldX == u) continue;
      auto [oldPrev, oldNext] = get_neighbor(k, x[k]);
      if (oldNext != 0) {
        segtree.update(oldNext, oldPrev);
      }
      x[k] = u;
      posOfX[u].insert(k);
      auto it = posOfX[oldX].find(k);
      posOfX[oldX].erase(it);
      auto [newPrev, newNext] = get_neighbor(k, x[k]);
      if (newNext != 0) {
        segtree.update(newNext, k);
      }

      segtree.update(k, newPrev);
    } else {
      int a, b;
      cin >> a >> b;
      int nearestPrev = segtree.rangeMax(a, b);
      if (nearestPrev >= a) {
        cout << "NO" << endl;
      } else {
        cout << "YES" << endl;
      }
    }
  }

  return 0;
}