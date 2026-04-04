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

struct Fenwick {
  vi bit;
  Fenwick(int n) : bit(n + 1)
  {
  }

  void set(int k, int dt)
  {
    k += 1;
    for (; k < bit.size(); k += k & -k) {
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
    int cnt = 0;
    k += 1;
    for (; k > 0; k -= k & -k) {
      cnt += bit[k];
    }

    return cnt;
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vi emp(n);
  vi comp;
  vector<array<int, 3>> query;
  for (int i = 0; i < n; i++) {
    cin >> emp[i];
    comp.push_back(emp[i]);
  }

  while (q--) {
    char c;
    cin >> c;
    if (c == '!') {
      int k, x;
      cin >> k >> x;
      comp.push_back(x);
      query.push_back({1, k, x});
    } else {
      int a, b;
      cin >> a >> b;
      comp.push_back(a);
      comp.push_back(b);
      query.push_back({0, a, b});
    }
  }

  sort(all(comp));
  comp.erase(unique(all(comp)), comp.end());

  dbg(comp);

  Fenwick fenw(comp.size());
  for (auto& e : emp) {
    e = lower_bound(all(comp), e) - comp.begin();
    fenw.set(e, 1);
  }
  dbg(emp);
  dbg(fenw.bit);
  for (auto& qr : query) {
    qr[2] = lower_bound(all(comp), qr[2]) - comp.begin();
    if (qr[0] == 0) {
      qr[1] = lower_bound(all(comp), qr[1]) - comp.begin();
    } else
      qr[1]--;

    if (qr[0] == 1) {
      auto [t, k, x] = qr;
      int before, after;
      before = emp[k];
      after = x;
      emp[k] = after;
      fenw.set(before, -1);
      fenw.set(after, 1);
      dbg(fenw.bit);
    } else {
      auto [t, a, b] = qr;
      cout << fenw.query(a, b) << endl;
    }
  }

  return 0;
}