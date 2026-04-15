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
    ll sum, pref, suf, ans;
    Node() : sum(0), pref(0), suf(0), ans(0)
    {
    }
  };

  explicit SegmentTree(const vi& arr) : n(arr.size()), tree(4 * n)
  {
    build(arr, 1, 0, n - 1);
  }

  ll query(int l, int r)
  {
    Node node;
    query(1, 0, n - 1, l, r, node);

    return max(0ll, node.ans);
  }

private:
  int n;
  vector<Node> tree;

  void query(int at, int al, int ar, int l, int r, Node& node)
  {
    if (ar < l || al > r) return;
    if (l <= al && ar <= r) {
      node = conquer(node, tree[at]);
      return;
    }

    int mid = (al + ar) / 2;
    query(2 * at, al, mid, l, r, node);
    query(2 * at + 1, mid + 1, ar, l, r, node);
  }

  void build(const vi& arr, int at, int al, int ar)
  {
    if (al == ar) {
      auto& node = tree[at];
      node.ans = node.pref = node.suf = node.sum = arr[al];
      return;
    }

    int mid = (al + ar) / 2;
    build(arr, 2 * at, al, mid);
    build(arr, 2 * at + 1, mid + 1, ar);

    tree[at] = conquer(tree[2 * at], tree[2 * at + 1]);
  }

  Node conquer(const Node& L, const Node& R)
  {
    Node node;
    node.sum = L.sum + R.sum;
    node.pref = max(L.pref, L.sum + R.pref);
    node.suf = max(R.suf, R.sum + L.suf);
    node.ans = max({L.ans, R.ans, L.suf + R.pref});

    return node;
  }
};

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, q;
  cin >> n >> q;

  vi nums(n);
  for (int i = 0; i < n; i++) cin >> nums[i];

  SegmentTree segtree(nums);
  while (q--) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    cout << segtree.query(a, b) << endl;
  }

  return 0;
}