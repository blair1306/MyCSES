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

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, x;
  cin >> n >> x;
  vi arr(n + 1);
  vll pref_sum(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    pref_sum[i] = pref_sum[i - 1] + arr[i];
  }
  map<ll, int> freq;
  freq[0] = 1;
  ll ans = 0;

  /*To calculate the number of subarrays that end at position i and have sum x, we should find all
  values j<i for which
  s(i) - s(j) = x
  which is equivalent to
  s(j) = s(i) - x.
  */

  for (int i = 1; i <= n; i++) {
    ll need = pref_sum[i] - x;
    if (freq.find(need) != freq.end()) {
      ans += freq[need];
    }

    freq[pref_sum[i]]++;
  }

  cout << ans << endl;

  return 0;
}