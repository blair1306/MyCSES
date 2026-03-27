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
0, 0, ->
*/
typedef vector<string> vs;

const int BOARD_SIZE = 8;

int solve(const vs& board)
{
  int ans = 0;
  vi col_used(BOARD_SIZE);
  vi diag1_used(BOARD_SIZE * 2 - 1);
  vi diag2_used(BOARD_SIZE * 2 - 1);

  function<void(int)> dfs = [&](int row) -> void {
    if (row == BOARD_SIZE) {
      ans++;
      return;
    }

    for (int col = 0; col < BOARD_SIZE; col++) {
      if (board[row][col] == '*') continue;

      int& c = col_used[col];
      int& d1 = diag1_used[row + col];
      int& d2 = diag2_used[row - col + BOARD_SIZE - 1];

      if (c || d1 || d2) continue;
      c = d1 = d2 = 1;
      dfs(row + 1);
      c = d1 = d2 = 0;
    }
  };

  dfs(0);

  return ans;
}

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  vs board(BOARD_SIZE);

  for (int i = 0; i < BOARD_SIZE; i++) cin >> board[i];
  int ans;
  ans = solve(board);

  cout << ans << endl;

  return 0;
}