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

typedef pii pos;
typedef vector<pos> vpos;

#define is_valid(pos, n) (pos.first >= 0 && pos.first < n && pos.second >= 0 && pos.second < n)

vector<pos> get_valid_pos(const pos& p, int n)
{
  vpos valid_pos;
  vpos diff = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
  for (auto [x, y] : diff) {
    pos nxt;
    nxt.first = p.first + x;
    nxt.second = p.second + y;
    if (is_valid(nxt, n)) valid_pos.push_back(nxt);
  }

  return valid_pos;
}

vvi solve(int n)
{
  vvi board(n, vi(n, -1));
  board[0][0] = 0;

  queue<pos> q;
  q.push({0, 0});

  while (q.size()) {
    pos p = q.front();
    q.pop();
    for (auto nxt : get_valid_pos(p, n)) {
      if (board[nxt.first][nxt.second] >= 0) continue;
      q.push(nxt);
      board[nxt.first][nxt.second] = board[p.first][p.second] + 1;
    }
  }

  return board;
}

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  cin >> n;
  vvi board = solve(n);
  for (auto row : board) {
    for (auto i : row) cout << i << " ";
    cout << endl;
  }

  return 0;
}