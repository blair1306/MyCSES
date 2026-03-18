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
  int left;
  int right;
  int idx;
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  cin >> n;
  vector<Range> ranges;
  vi contain(n);
  vi contained(n);

  for (int i = 0; i < n; i++) {
    Range r;
    cin >> r.left >> r.right;
    r.idx = i;
    ranges.push_back(r);
  }

  sort(all(ranges), [](const Range& lhs, const Range& rhs) {
    if (lhs.left == rhs.left)
      return lhs.right > rhs.right;
    else
      return lhs.left < rhs.left;
  });

#ifdef LOCAL
  for (auto r : ranges) cerr << "[" << r.left << "," << r.right << "]" << "#" << r.idx << endl;
#endif

  int max_r = ranges[0].right;
  for (int i = 1; i < n; i++) {
    auto range = ranges[i];
    if (range.right > max_r) {
      max_r = range.right;
      continue;
    }
    contained[i] = 1;
  }

  int min_r = ranges[n - 1].right;
  for (int i = n - 2; i >= 0; i--) {
    auto range = ranges[i];
    if (range.right < min_r) {
      min_r = range.right;
      continue;
    }
    contain[i] = 1;
  }

  for (int i = 0; i < n; i++) cout << contain[i] << " ";
  cout << endl;
  for (int i = 0; i < n; i++) cout << contained[i] << " ";

  return 0;
}