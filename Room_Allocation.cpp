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

typedef array<int, 3> customer;

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  cin >> n;
  vi room_num(n);
  vector<customer> customers;

  for (int i = 0; i < n; i++) {
    customer cus;
    cin >> cus[0] >> cus[1];
    cus[2] = i;
    customers.push_back(cus);
  }

  sort(all(customers));

  priority_queue<pii> pq;  // {departure, id}

  auto [arrival, departure, idx] = customers[0];
  room_num[idx] = 1;
  pq.push({-departure, idx});
  for (int i = 1; i < n; i++) {
    auto [arrival, departure, idx] = customers[i];
    auto [last_departure, last_idx] = pq.top();
    if (last_departure <= -arrival) {
      pq.push({-departure, idx});
      room_num[idx] = pq.size();
    } else {
      room_num[idx] = room_num[last_idx];
      pq.pop();
      pq.push({-departure, idx});
    }
  }

  cout << pq.size() << endl;
  for (auto r : room_num) cout << r << " ";

  return 0;
}