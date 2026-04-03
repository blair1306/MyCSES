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

class Segtree {
public:
  Segtree(int _n) : n(_n), segtree(n * 4)
  {
    build(1, 0, n - 1, vi(n, 1));
  }

  void set(int k)
  {
    set(1, 0, n - 1, k);
  }

  int find_pos(int k)
  {
    return find_pos(1, 0, n - 1, k);
  }

  int n;
  vi segtree;

private:
  int conquer(int at) const
  {
    return segtree[2 * at] + segtree[2 * at + 1];
  }

  void set(int at, int al, int ar, int k)
  {
    if (al == ar) {
      segtree[at] = 0;
      return;
    }

    int mid = al + (ar - al) / 2;
    if (k <= mid)
      set(2 * at, al, mid, k);
    else
      set(2 * at + 1, mid + 1, ar, k);

    segtree[at] = conquer(at);
  }

  int find_pos(int at, int al, int ar, int k)
  {
    if (segtree[at] < k) return -1;
    if (al == ar) return al;

    int mid = (al + ar) / 2;
    if (k <= segtree[2 * at])
      return find_pos(2 * at, al, mid, k);
    else {
      k -= segtree[2 * at];
      return find_pos(2 * at + 1, mid + 1, ar, k);
    }
  }

  void build(int at, int al, int ar, const vi& arr)
  {
    if (al == ar) {
      segtree[at] = arr[al];
      return;
    }

    int mid = al + (ar - al) / 2;
    build(2 * at, al, mid, arr);
    build(2 * at + 1, mid + 1, ar, arr);

    segtree[at] = conquer(at);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  cin >> n;

  Segtree segtree(n);
  dbg(segtree.segtree);
  vi nums(n);
  for (int i = 0; i < n; i++) cin >> nums[i];
  while (n--) {
    int k;
    cin >> k;
    int pos = segtree.find_pos(k);
    cout << nums[pos] << " ";
    segtree.set(pos);
  }

  return 0;
}