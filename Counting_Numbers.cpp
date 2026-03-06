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

#define POS 20
#define TIGHT 2
#define LEADING0 2
#define LAST_DIGIT 11  // 10 represents invalid
ll memo[POS][TIGHT][LEADING0][LAST_DIGIT];
string num;

ll dfs(int pos, int tight, int leading0, int last_digit)
{
  if (pos == num.size()) return 1;
  ll& res = memo[pos][tight][leading0][last_digit];
  if (res != -1) return res;

  res = 0;  // !!! Reset before accumulating

  int limit = tight ? num[pos] - '0' : 9;

  for (int d = 0; d <= limit; d++) {
    int new_tight = tight && (d == limit);
    int new_leading0 = leading0 && (d == 0);
    int new_last = new_leading0 ? 10 : d;
    if (!new_leading0 && (last_digit != 10) && last_digit == d) continue;
    res += dfs(pos + 1, new_tight, new_leading0, new_last);
  }

  return res;
}

ll count_valid(ll x)
{
  if (x < 0) return 0;
  num = to_string(x);
  memset(memo, -1, sizeof(memo));  // !!!Always memset using the variable you are clearing.
  return dfs(0, 1, 1, 10);
}

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  ll a, b;
  cin >> a >> b;

  cout << count_valid(b) - count_valid(a - 1) << endl;

  return 0;
}