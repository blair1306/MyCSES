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

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, target;
  cin >> n >> target;

  vi arr(n);
  vpii aux(n);

  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;
    arr[i] = num;
    aux[i] = {num, i + 1};
  }

  sort(all(arr));
  sort(all(aux));

  for (int i = 0; i < n; i++) {
    int num;
    num = arr[i];
    auto it = upper_bound(arr.begin(), arr.end(), target - num);
    if (it == arr.begin()) continue;
    it--;
    if ((*it) + num == target) {
      int other_idx = it - arr.begin();
      if (other_idx == i) continue;
      dbg(other_idx, num);
      cout << aux[i].second << " " << aux[other_idx].second << endl;
      return 0;
    }
  }

  cout << "IMPOSSIBLE" << endl;

  return 0;
}