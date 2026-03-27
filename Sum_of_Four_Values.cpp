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

struct IdNum {
  int x, id;
  bool operator<(const IdNum& other) const
  {
    return x < other.x;
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, t;
  cin >> n >> t;
  map<ll, vector<pii>> sum_map;

  vector<IdNum> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i].x;
    nums[i].id = i + 1;
  }

  sort(all(nums));

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      ll sum = nums[i].x + nums[j].x;
      sum_map[sum].push_back({nums[i].id, nums[j].id});
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      ll need = t - nums[i].x - nums[j].x;
      int iid = nums[i].id, jid = nums[j].id;
      for (auto [m, n] : sum_map[need]) {
        if (m != iid && m != jid && n != iid && n != jid) {
          cout << m << " " << n << " " << iid << " " << jid << endl;
          return 0;
        }
      }
    }
  }

  cout << "IMPOSSIBLE" << endl;

  return 0;
}