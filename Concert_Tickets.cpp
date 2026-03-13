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

/*

There are n concert tickets available, each with a certain price. Then, m customers arrive, one
after another. Each customer announces the maximum price they are willing to pay for a ticket, and
after this, they will get a ticket with the nearest possible price such that it does not exceed the
maximum price. Input The first input line contains integers n and m: the number of tickets and the
number of customers. The next line contains n integers h_1,h_2,\ldots,h_n: the price of each ticket.
The last line contains m integers t_1,t_2,\ldots,t_m: the maximum price for each customer in the
order they arrive. Output Print, for each customer, the price that they will pay for their ticket.
After this, the ticket cannot be purchased again. If a customer cannot get any ticket, print -1.
Constraints

1 \le n, m \le 2 \cdot 10^5
1 \le h_i, t_i \le 10^9

Example
Input:
5 3
5 3 7 8 5
4 8 3

Output:
3
8
-1*/

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  multiset<int> tickets;
  for (int i = 0; i < n; i++) {
    int ticket;
    cin >> ticket;
    tickets.insert(ticket);
  }

  for (int i = 0; i < m; i++) {
    int customer;
    cin >> customer;
    // 1. Find the first ticket price > customer
    auto it = tickets.upper_bound(customer);
    if (it == tickets.begin()) {
      cout << -1 << endl;
      continue;
    }

    // Step back to find the largest price <= customer
    it--;
    cout << *it << endl;
    tickets.erase(it);
  }

  return 0;
}