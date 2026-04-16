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

class Fenwick {
public:
  explicit Fenwick(int n) : bit(n + 1)
  {
  }

  void set(int k, int dt)
  {
    for (k += 1; k < (int)bit.size(); k += k & -k) {
      bit[k] += dt;
    }
  }

  int query(int a, int b)
  {
    int ans = query(b);
    if (a > 0) ans -= query(a - 1);

    return ans;
  }

  int query(int k)
  {
    int ans = 0;
    for (k += 1; k > 0; k -= k & -k) {
      ans += bit[k];
    }

    return ans;
  }

  vi bit;

private:
};

struct Query {
  int a, b, id;
  bool operator<(const Query& other) const
  {
    return b < other.b;
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;
  unordered_map<int, int> prevValueMap;
  vi prev(n);

  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;
    if (prevValueMap.count(v)) {
      prev[i] = prevValueMap[v];
    } else {
      prev[i] = -1;
    }
    prevValueMap[v] = i;
  }

  dbg(prev);
  // offline process
  vector<Query> queries;
  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    queries.push_back({a, b, i});
  }

  Fenwick bit(n);
  vi ans(q);

  sort(all(queries));
  int sweep = 0;
  for (const auto& query : queries) {
    auto [a, b, id] = query;
    int r = b;
    for (; sweep <= r; sweep++) {
      bit.set(sweep, 1);
      if (prev[sweep] >= 0) bit.set(prev[sweep], -1);
    }

    dbg(bit.bit);

    ans[id] = bit.query(a, b);
  }

  /*
  3, 3
  1, 2
  prev[0] = -1, prev[1] = 0
  sweep = 0, bit.set(0, 1)
  sweep = 1, bit.set(1, 1), bit.set(0, -1)
  Ha, we didn't set bit.set(**0**, -1), case closed
  */

  for (auto a : ans) cout << a << endl;

  return 0;
}