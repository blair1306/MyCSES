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

class SegmentTree {
public:
  struct Node {
    ll sum, prev, suf, ans;
  };
  SegmentTree(const vi& arr) : n(arr.size()), tree(4 * n)
  {
    build(arr, 1, 0, n - 1);
  };
  void update(int k, int x)
  {
    update(1, 0, n - 1, k, x);
  }

  ll query()
  {
    ll ans = 0;
    auto node = tree[1];

    return node.ans;
  }

private:
  int n;
  vector<Node> tree;

  void update(int at, int al, int ar, int k, int x)
  {
    if (al == ar) {
      auto& node = tree[at];
      node.sum = node.prev = node.suf = node.ans = x;
      return;
    }

    int mid = (al + ar) / 2;
    if (k <= mid)
      update(2 * at, al, mid, k, x);
    else
      update(2 * at + 1, mid + 1, ar, k, x);

    tree[at] = conquer(tree[2 * at], tree[2 * at + 1]);
  }

  Node conquer(const Node& l, const Node& r)
  {
    Node node;
    node.sum = l.sum + r.sum;
    node.prev = max(l.prev, l.sum + r.prev);
    node.suf = max(r.suf, r.sum + l.suf);
    node.ans = max({node.sum, l.sum, r.sum, l.suf + r.prev});

    return node;
  }

  void build(const vi& arr, int at, int al, int ar)
  {
    if (al == ar) {
      auto& node = tree[at];
      node.sum = node.prev = node.suf = arr[al];
      return;
    }

    int mid = (al + ar) / 2;
    build(arr, 2 * at, al, mid);
    build(arr, 2 * at + 1, mid + 1, ar);

    tree[at] = conquer(tree[2 * at], tree[2 * at + 1]);
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vi nums(n);
  for (int i = 0; i < n; i++) cin >> nums[i];
  SegmentTree segtree(nums);

  while (m--) {
    int k, x;
    cin >> k >> x;
    k--;
    segtree.update(k, x);
    cout << segtree.query() << endl;
  }

  return 0;
}