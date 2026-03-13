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

typedef vector<pii> vpii;
typedef map<int, int> mii;

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  mii ticket_cnt_by_price;
  vi ticket;

  for (int i = 0; i < n; i++) {
    int ticket_price;
    cin >> ticket_price;
    if (ticket_cnt_by_price.count(ticket_price) == 0) {
      ticket.push_back(ticket_price);
    }
    ticket_cnt_by_price[ticket_price]++;
  }

  sort(ticket.begin(), ticket.end());

  for (int i = 0; i < m; i++) {
    int customer_price, ticket_idx;
    cin >> customer_price;
    ticket_idx = lower_bound(all(ticket), customer_price) - ticket.begin();
    if (ticket_idx == ticket.size() || ticket_cnt_by_price[ticket_idx] == 0) {
      cout << -1 << endl;
      continue;
    }
    cout << ticket[ticket_idx] << endl;
    ticket_cnt_by_price[ticket_idx]--;
  }

  return 0;
}