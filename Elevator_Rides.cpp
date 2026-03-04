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
const int N = 20 + 1;     // size for global arrays (if needed)

struct State {
  int n;
  int cur_weight;
  bool operator<(const State& other)
  {
    if (n != other.n) return n - other.n;
    return cur_weight - other.cur_weight;
  }
};

pii state[1 << N];

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  int max_cap;
  cin >> n;
  cin >> max_cap;
  vi weight(n);
  for (int i = 0; i < n; i++) {
    cin >> weight[i];
  }

  state[0] = {1, 0};
  for (int S = 1; S < (1 << n); S++) {
    state[S].first = n + 1;  // number of rides
    state[S].second = 0;     // current weight
    for (int i = 0; i < n; i++) {
      if (!(S & (1 << i))) continue;
      auto sub_state = state[S ^ (1 << i)];
      if (sub_state.second + weight[i] <= max_cap) {
        sub_state.second += weight[i];
      } else {
        sub_state.first++;
        sub_state.second = weight[i];
      }
      // dbg(state[S], sub_state);
      state[S] = min(state[S], sub_state);
    }
  }

  cout << state[(1 << n) - 1].first << endl;

  return 0;
}