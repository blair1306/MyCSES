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

struct BIT {
  vll b1, b2;  // (i+1) b1 - (j) b2;

  BIT(int n) : b1(n + 2), b2(n + 2)
  {
  }

  void add(vll& bit, int k, ll v)
  {
    for (; k < bit.size(); k += k & -k) bit[k] += v;
  }

  ll query(vll& bit, int k)
  {
    ll ret = 0;
    for (; k > 0; k -= k & -k) ret += bit[k];

    return ret;
  }

  void range_add(int a, int b, ll v)
  {
    add(b1, a, v);
    add(b2, a, a * v);
    add(b1, b + 1, -v);
    add(b2, b + 1, -(b + 1) * v);
  }

  ll range_sum(int a, int b)
  {
    return pref_sum(b) - pref_sum(a - 1);
  }

  ll pref_sum(int k)
  {
    return (ll)(k + 1) * query(b1, k) - query(b2, k);
  }
};

struct Query {
  int a, b, i;
};

struct Plateau {
  int a, b, v;
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vi x(n + 1);
  vll xPref(n + 2);

  for (int i = 1; i <= n; i++) {
    cin >> x[i];
    xPref[i] = xPref[i - 1] + x[i];
  }

  vll ans(q);
  map<int, vector<Query>> queryByA;

  for (int i = 0; i < q; i++) {
    Query qry;
    cin >> qry.a >> qry.b;
    qry.i = i;
    queryByA[qry.a].push_back(qry);
  }

  stack<Plateau> stk;
  BIT bit(n);

  for (int i = n; i > 0; i--) {
    int end = i;
    while (!stk.empty() && stk.top().v < x[i]) {
      auto [a, b, vOld] = stk.top();
      stk.pop();
      bit.range_add(a, b, -vOld);
      end = b;
    }

    bit.range_add(i, end, x[i]);
    stk.push({i, end, x[i]});

    for (auto [a, b, i] : queryByA[i]) {
      ll runningMax = bit.range_sum(a, b);
      ll prefSum = xPref[b] - xPref[a - 1];
      ans[i] = runningMax - prefSum;
    }
  }

  for (auto s : ans) cout << s << endl;

  return 0;
}