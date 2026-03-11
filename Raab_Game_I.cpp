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
Consider a two player game where each player has n cards numbered 1,2,\dots,n. On each turn both players place one of their cards on the table. The player who placed the higher card gets one point. If the cards are equal, neither player gets a point. The game continues until all cards have been played.
You are given the number of cards n and the players' scores at the end of the game, a and b. Your task is to give an example of how the game could have played out.
Input
The first line contains one integer t: the number of tests.
Then there are t lines, each with three integers n, a and b.
Output
For each test case print YES if there is a game with the given outcome and NO otherwise.
If the answer is YES, print an example of one possible game. Print two lines representing the order in which the players place their cards. You can give any valid example.
Constraints

1 \le t \le 1000
1 \le n \le 100
0 \le a,b \le n

Example
Input:
5
4 1 2
2 0 1
3 0 0
2 1 1
4 4 1

Output:
YES
1 4 3 2
2 1 3 4
NO
YES
1 2 3
1 2 3
YES
1 2
2 1
NO
*/

void solve(int n, int a, int b)
{
  vi card;
  bool found = false;
  for (int i = 0; i <= n; i++) card.push_back(i);

  function<void(int, int, int)> bfs = [&](int start, int a, int b) {
    if (a < 0 || b < 0) return;
    if (start > n && a == 0 && b == 0) found = true;
    if (found) return;

    dbg(start, card);

    int diff;  // card a - card b(1...n)
    int na = a, nb = b;

    for (int i = start; i <= n; i++) {
      swap(card[start], card[i]);
      diff = card[i] - i;
      if (diff >= 0)
        na = a - 1;
      else
        nb = b - 1;
      bfs(start + 1, na, nb);
      swap(card[start], card[i]);
    }
  };

  bfs(1, a, b);

  if (!found) {
    cout << "NO" << endl;
    return;
  }

  cout << "YES" << endl;
  for (int c : card) cout << c << " " << endl;
  for (int i = 1; i <= n; i++) cout << i << " " << endl;
}

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    int n, a, b;
    cin >> n >> a >> b;
    solve(n, a, b);
  }

  return 0;
}