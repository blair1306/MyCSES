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

struct Range {
  int l;
  int r;
  int idx;
};

struct Fenwick {
  vi tree;
  Fenwick(int n) : tree(n + 1) {};
  void update(int k, int dt)
  {
    k = k + 1;
    for (; k < tree.size(); k += (k & -k)) {
      tree[k] += dt;
    }
  }

  int query(int k)
  {
    int ans = 0;
    k = k + 1;
    for (; k > 0; k -= (k & -k)) {
      ans += tree[k];
    }

    return ans;
  }

  void reset()
  {
    fill(all(tree), 0);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  cin >> n;
  vi comp;
  // set<int> comp;

  vector<Range> ranges;
  for (int i = 0; i < n; i++) {
    Range range;
    cin >> range.l >> range.r;
    comp.push_back(range.r);
    range.idx = i;
    ranges.push_back(range);
  }

  sort(ranges.begin(), ranges.end(), [](const Range& lhs, const Range& rhs) {
    if (lhs.l == rhs.l)
      return lhs.r > rhs.r;
    else
      return lhs.l < rhs.l;
  });

  dbg(ranges[0].l);
  sort(all(comp));
  auto last = unique(all(comp));
  comp.erase(last, comp.end());

  for (auto& range : ranges) {
    range.r = lower_bound(all(comp), range.r) - comp.begin();
  }

  Fenwick fenw(comp.size());
  vi contains(n);
  vi contained_by(n);
  int r, idx;
  for (int i = 0; i < n; i++) {
    r = ranges[i].r, idx = ranges[i].idx;
    contained_by[idx] = i - fenw.query(r - 1);
    fenw.update(r, 1);
  }
  fenw.reset();
  for (int i = n - 1; i >= 0; i--) {
    r = ranges[i].r, idx = ranges[i].idx;
    contains[idx] = fenw.query(r);
    fenw.update(r, 1);
  }

  for (auto c : contains) cout << c << " ";
  cout << endl;
  for (auto c : contained_by) cout << c << " ";

  return 0;
}