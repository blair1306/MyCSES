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

// ── Segment tree: range max, point update ────────────────────────────────────
struct MaxSegTree {
  int n;
  vector<int> tree;

  MaxSegTree(const vector<int>& a) : n(a.size()), tree(4 * a.size())
  {
    build(a, 1, 0, n - 1);
  }

  void update(int pos, int val)
  {
    update(1, 0, n - 1, pos, val);
  }
  int query(int l, int r)
  {
    return query(1, 0, n - 1, l, r);
  }

private:
  void build(const vector<int>& a, int node, int lo, int hi)
  {
    if (lo == hi) {
      tree[node] = a[lo];
      return;
    }
    int mid = (lo + hi) / 2;
    build(a, 2 * node, lo, mid);
    build(a, 2 * node + 1, mid + 1, hi);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
  }

  void update(int node, int lo, int hi, int pos, int val)
  {
    if (lo == hi) {
      tree[node] = val;
      return;
    }
    int mid = (lo + hi) / 2;
    if (pos <= mid)
      update(2 * node, lo, mid, pos, val);
    else
      update(2 * node + 1, mid + 1, hi, pos, val);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
  }

  int query(int node, int lo, int hi, int l, int r)
  {
    if (hi < l || lo > r) return 0;
    if (l <= lo && hi <= r) return tree[node];
    int mid = (lo + hi) / 2;
    return max(query(2 * node, lo, mid, l, r), query(2 * node + 1, mid + 1, hi, l, r));
  }
};

// ── Main ─────────────────────────────────────────────────────────────────────
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  unordered_map<int, set<int>> positions;  // value → sorted set of indices
  vector<int> x(n + 1);                    // current array values
  vector<int> prevOcc(n + 1);              // prevOcc[i] = last index j<i with x[j]==x[i]

  // ── helpers ──────────────────────────────────────────────────────────────
  // Returns the nearest index before k that holds value v (0 if none)
  auto prevOf = [&](int k, int v) -> int {
    auto& S = positions[v];
    auto it = S.lower_bound(k);
    return (it != S.begin()) ? *std::prev(it) : 0;
  };

  // Returns the nearest index after k that holds value v (0 if none)
  auto nextOf = [&](int k, int v) -> int {
    auto& S = positions[v];
    auto it = S.upper_bound(k);
    return (it != S.end()) ? *it : 0;
  };

  // ── build initial prevOcc ─────────────────────────────────────────────
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
    prevOcc[i] = prevOf(i, x[i]);  // before inserting i
    positions[x[i]].insert(i);
  }

  MaxSegTree seg(prevOcc);

  // ── queries ───────────────────────────────────────────────────────────
  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int k, u;
      cin >> k >> u;
      if (x[k] == u) continue;

      int oldVal = x[k];

      // 1. oldVal's successor now skips over k → its prev becomes k's prev
      int oNext = nextOf(k, oldVal);
      if (oNext) seg.update(oNext, prevOcc[k]);

      // 2. Remove k from old value, insert into new value
      positions[oldVal].erase(k);
      positions[u].insert(k);
      x[k] = u;

      // 3. k's own prev changes to nearest predecessor with value u
      prevOcc[k] = prevOf(k, u);
      seg.update(k, prevOcc[k]);

      // 4. u's successor now points back to k instead of k's predecessor
      int nNext = nextOf(k, u);
      if (nNext) seg.update(nNext, k);

    } else {
      int a, b;
      cin >> a >> b;
      // All distinct iff no element in [a,b] has a duplicate within [a,b]
      // ↔ max(prevOcc[a..b]) < a
      cout << (seg.query(a, b) < a ? "YES" : "NO") << '\n';
    }
  }
}