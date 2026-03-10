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

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  /*
  Your task is to calculate the number of bit strings of length n.
  For example, if n=3, the correct answer is 8, because the possible bit strings are 000, 001, 010,
  011, 100, 101, 110, and 111. Input The only input line has an integer n. Output Print the result
  modulo 10^9+7. Constraints

  1 \le n \le 10^6

  Example
  Input:
  3

  Output:
  8
  */

  int n;
  cin >> n;
  ll ans = 1;
  ll base = 2;

  while (n > 0) {
    if (n & 1) {
      ans = (ans * base) % MOD;
    }
    base = (base * base) % MOD;
    n >>= 1;
  }

  cout << ans << endl;

  return 0;
}