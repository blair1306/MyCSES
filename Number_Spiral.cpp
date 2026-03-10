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

/*
https://cses.fi/problemset/task/1071

A number spiral is an infinite grid whose upper-left square has number 1. Here are the first five
layers of the spiral:

 1  2  8 19 25
 4  3  8 11 24
 5  6  7 12 23
16 15 14 13 22
17 18 19 10 21

Your task is to find out the number in row y and column x.
Input
The first input line contains an integer t: the number of tests.
After this, there are t lines, each containing integers y and x.
Output
For each test, print the number in row y and column x.
Constraints

1 \le t \le 10^5
1 \le y,x \le 10^9

Example
Input:
3
2 3
1 1
4 2

Output:
8
1
15
*/

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    ll y, x;
    cin >> y >> x;
    ll n = max(x, y);
    ll ans;

    // when n is even, the max point is n^2 at (1, n) else it is at (n, 1)
    if (n & 1) {
      if (x == n)
        ans = n * n - (y - 1);
      else
        ans = (n - 1) * (n - 1) + 1 + x - 1;
    } else {
      if (x == n)
        ans = (n - 1) * (n - 1) + 1 + y - 1;
      else
        ans = n * n - (x - 1);
    }

    cout << ans << endl;
  }

  return 0;
}