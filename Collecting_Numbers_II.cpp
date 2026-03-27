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
You are given an array that contains each number between 1 \dots n exactly once. Your task is to
collect the numbers from 1 to n in increasing order. On each round, you go through the array from
left to right and collect as many numbers as possible. Given m operations that swap two numbers in
the array, your task is to report the number of rounds after each operation. Input The first line
has two integers n and m: the array size and the number of operations. The next line has n integers
x_1,x_2,\dots,x_n: the numbers in the array. Finally, there are m lines that describe the
operations. Each line has two integers a and b: the numbers at positions a and b are swapped. Output
Print m integers: the number of rounds after each swap.
Constraints

1 \le n, m \le 2 \cdot 10^5
1 \le a,b \le n

Example
Input:
5 3
4 2 1 5 3
2 3
1 5
2 3

Output:
2
3
4*/

int get_inv_at(const vi& pos, int x, int y)
{
  int ret = 0;
  if (x == y) return 0;
  if (x > y) swap(x, y);

  if (pos[x - 1] > pos[x]) ret++;
  if (((x + 1) != y) && pos[x] > pos[x + 1]) ret++;  // if x+1=y then x, x+1 is same as y-1, y
  if (pos[y - 1] > pos[y]) ret++;
  if (pos[y] > pos[y + 1]) ret++;

  return ret;
}

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  /*
  4 2 1 5 3
   1 2   3
  4 1 2 5 3

  4 2 1 5 3
   1 2   3
  3 2 1 5 4
   1 2   3
   */
  int n, m;
  cin >> n >> m;
  vi pos(n + 1);
  vi num(n + 1);

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    pos[x] = i;
    num[i] = x;
  }

  pos.push_back(INF);
  num.push_back(INF);

  int ninv = 0;
  for (int i = 1; i <= n; i++) {
    if (pos[i] < pos[i - 1]) ninv++;
  }

  dbg(ninv);

  while (m--) {
    int a, b;
    int x, y;
    int before, after;
    cin >> a >> b;
    x = num[a];
    y = num[b];
    before = get_inv_at(pos, x, y);
    dbg(num, pos);
    swap(pos[x], pos[y]);
    swap(num[a], num[b]);
    dbg(num, pos);
    after = get_inv_at(pos, x, y);
    dbg(before, after);
    ninv += after - before;
    cout << ninv + 1 << endl;
  }

  return 0;
}