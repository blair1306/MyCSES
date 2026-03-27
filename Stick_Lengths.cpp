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
There are n sticks with some lengths. Your task is to modify the sticks so that each stick has the
same length. You can either lengthen and shorten each stick. Both operations cost x where x is the
difference between the new and original length. What is the minimum total cost? Input The first
input line contains an integer n: the number of sticks. Then there are n integers:
p_1,p_2,\ldots,p_n: the lengths of the sticks. Output Print one integer: the minimum total cost.
Constraints

1 \le n \le 2 \cdot 10^5
1 \le p_i \le 10^9

Example
Input:
5
2 3 1 5 2

Output:
5
*/
int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  cin >> n;

  ll median1, median2;
  vll sticks(n);

  for (int i = 0; i < n; i++) {
    ll stick;
    cin >> stick;
    sticks[i] = stick;
  }

  sort(all(sticks));
  /*
    minimizing sum of squared differences → mean
    minimizing sum of absolute differences → median
  */
  if (n & 1) {
    median1 = median2 = n / 2;
  } else {
    median1 = n / 2;
    median2 = median1 - 1;
  }

  ll length1 = sticks[median1];
  ll length2 = sticks[median2];
  ll sum1 = 0;
  ll sum2 = 0;

  for (int stick : sticks) {
    sum1 += abs(stick - length1);
    sum2 += abs(stick - length2);
  }

  cout << min(sum1, sum2) << endl;

  return 0;
}