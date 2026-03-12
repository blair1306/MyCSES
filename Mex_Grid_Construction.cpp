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
const int N = 100;  // size for global arrays (if needed)
#endif

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  cin >> n;

  // int grid[N][N];
  vvi grid(n, vi(n, 0));

  for (int col = 0; col < n; col++) {
    for (int row = 0; row < col; row++) {
      if (row == 0) {
        grid[row][col] = col;
        continue;
      }
      if ((col & 1) == 0)
        grid[row][col] = grid[row - 1][col] + 1;
      else
        grid[row][col] = grid[row - 1][col] - 1;
    }
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < row; col++) {
      if (col == 0) {
        grid[row][col] = row;
        continue;
      }
      if ((row & 1) == 0)
        grid[row][col] = grid[row][col - 1] + 1;
      else
        grid[row][col] = grid[row][col - 1] - 1;
    }
  }

  for (int row = 0; row < n; row++) {
    for (int n : grid[row]) cout << n << " ";
    cout << endl;
  }

  for (int i = 1; i < n; i++) return 0;
}