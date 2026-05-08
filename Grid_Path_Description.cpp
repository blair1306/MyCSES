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
const int N = 7;          // size for global arrays (if needed)

int grid[N + 2][N + 2];
// int vis[N + 2][N + 2][4];
vector<char> path;
const int pathMaxSz = (N * N) - 1;
int ans = 0;

struct Direction {
  char d;
  int dx, dy, di;
};

Direction dirs[] = {{'D', 0, 1, 0}, {'U', 0, -1, 1}, {'L', -1, 0, 2}, {'R', 1, 0, 3}};
string pathDesc;

void dfs(int y, int x, int d = 0)
{
  if (grid[y][x] == 1) return;
  if ((y == N && x == 1) || path.size() == pathMaxSz) {
    if ((y == N && x == 1) && path.size() == pathMaxSz) ans++;
    return;
  }

  grid[y][x] = 1;

  // if (vis[y][x][d] == 1) return;
  // vis[y][x][d] = 1;

  char nextDir = pathDesc[path.size()];

  for (auto [dir, dx, dy, di] : dirs) {
    if (nextDir != '?' && nextDir != dir) continue;
    path.push_back(dir);
    dbg(path);
    dfs(y + dy, x + dx, di);
    path.pop_back();
  }

  grid[y][x] = 0;
}

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  cin >> pathDesc;

  for (int c = 0; c <= N + 1; c++) {
    grid[0][c] = 1;
    grid[N + 1][c] = 1;
  }

  for (int r = 0; r <= N + 1; r++) {
    grid[r][0] = 1;
    grid[r][N + 1] = 1;
  }

  dbg(grid);
  dfs(1, 1);

  cout << ans << endl;

  return 0;
}