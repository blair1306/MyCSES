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

template <typename T>
class Segtree {
public:
  using Arr = vector<T>;
  Segtree(const Arr& _arr) : n(_arr.size()), arr(n * 4)
  {
    build(1, 0, n - 1, _arr);
  }

  int find(T nRoom) const
  {
    return find(1, 0, n - 1, nRoom);
  }

  void set(int k, T v)
  {
    return set(1, 0, n - 1, k, v);
  }

  int n;
  Arr arr;

private:
  T conquer(int at) const
  {
    return max(arr[2 * at], arr[2 * at + 1]);
  }

  void build(int at, int al, int ar, const Arr& _arr)
  {
    if (al == ar) {
      arr[at] = _arr[al];
      return;
    }

    int mid = al + (ar - al) / 2;
    build(2 * at, al, mid, _arr);
    build(2 * at + 1, mid + 1, ar, _arr);

    arr[at] = conquer(at);
  }

  int find(int at, int al, int ar, T nRoom) const
  {
    if (arr[at] < nRoom) return -1;
    if (al == ar) return al;

    int mid = al + (ar - al) / 2;
    if (arr[2 * at] >= nRoom)
      return find(2 * at, al, mid, nRoom);
    else {
      return find(2 * at + 1, mid + 1, ar, nRoom);
    }
  }

  void set(int at, int al, int ar, int k, T v)
  {
    if (al == ar) {
      arr[at] = v;
      return;
    }

    int mid = al + (ar - al) / 2;
    if (k <= mid)
      set(2 * at, al, mid, k, v);
    else
      set(2 * at + 1, mid + 1, ar, k, v);

    arr[at] = conquer(at);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  cin >> n >> m;
  vi hotels(n);

  for (int i = 0; i < n; i++) {
    cin >> hotels[i];
  }

  Segtree<int> segtree(hotels);

  dbg(segtree.arr);

  while (m--) {
    int nRoom;
    cin >> nRoom;
    int pos = segtree.find(nRoom);
    cout << pos + 1 << " ";
    if (pos >= 0) {
      hotels[pos] -= nRoom;
      segtree.set(pos, hotels[pos]);
    }
  }

  return 0;
}