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
  explicit Fenwick(int n) : bit(n + 1)
  {
  }

  void add(int k, int dt)
  {
    for (++k; k < (int)bit.size(); k += k & -k) {
      bit[k] += dt;
    }
  }

  int sum(int k) const
  {
    int res = 0;
    for (++k; k > 0; k -= k & -k) {
      res += bit[k];
    }

    return res;
  }
};

struct Query {
  char type;
  int a, b;
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vi salary(n);
  vi coords;
  vector<Query> query;
  for (int i = 0; i < n; i++) {
    cin >> salary[i];
    coords.push_back(salary[i]);
  }

  while (q--) {
    char type;
    int a, b;
    cin >> type >> a >> b;
    query.push_back({type, a, b});

    if (type == '!') coords.push_back(b);
  }

  sort(all(coords));
  coords.erase(unique(all(coords)), coords.end());

  dbg(coords);

  auto id = [&](int x) { return (int)(lower_bound(all(coords), x) - coords.begin()); };

  Fenwick fenw(coords.size());
  for (int x : salary) {
    fenw.add(id(x), 1);
  }

  auto count_leq = [&](int x) {
    int pos = int(upper_bound(all(coords), x) - coords.begin()) - 1;
    return fenw.sum(pos);
  };

  for (auto [type, a, b] : query) {
    if (type == '!') {
      int k = a - 1;
      fenw.add(id(salary[k]), -1);
      salary[k] = b;
      fenw.add(id(salary[k]), +1);
    } else {
      cout << count_leq(b) - count_leq(a - 1) << endl;
    }
  }

  return 0;
}