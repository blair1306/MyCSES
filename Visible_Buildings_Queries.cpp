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

struct Query {
  int l, r;
  int id;
  int ans;
  const bool operator<(const Query& other) const
  {
    return l < other.l;
  }
};

struct Fenwick {
  vi bit;
  Fenwick(int n) : bit(n + 1)
  {
  }

  void update(int k, int v)
  {
    for (k += 1; k < bit.size(); k += k & -k) {
      bit[k] += v;
    }
  }

  int count(int k)
  {
    int ret = 0;
    for (k += 1; k > 0; k -= k & -k) {
      ret += bit[k];
    }

    return ret;
  }

  int count(int a, int b)
  {
    int ret = 0;
    ret += count(a);
    if (b > 0) ret -= count(b);

    return ret;
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vi building(n + 1);
  vvi group(n + 1);

  vector<Query> query(q);
  vi lastBloker;  // monotonic stack
  building[0] = INF;
  lastBloker.push_back(0);
  int activated = 0;

  for (int i = 1; i <= n; i++) {
    int b;
    cin >> b;
    building[i] = b;
    while (b > building[lastBloker.back()]) {
      lastBloker.pop_back();
    }
    group[lastBloker.back()].push_back(i);
    lastBloker.push_back(i);
  }

  dbg(group);
  for (int i = 0; i < q; i++) {
    auto& qr = query[i];
    qr.id = i;
    qr.ans = 0;
    cin >> qr.l >> qr.r;
  }

  sort(all(query));
  dbg(query[0].l);

  Fenwick fenw(n);
  vi ans(q);

  for (auto qr : query) {
    for (; activated < qr.l - 1; activated++) {
      for (auto bd : group[activated]) {
        fenw.update(bd, 1);
      }
    }

    ans[qr.id] = fenw.count(qr.l, qr.r);
  }
  dbg(fenw.bit);

  for (auto a : ans) cout << a << endl;

  return 0;
}