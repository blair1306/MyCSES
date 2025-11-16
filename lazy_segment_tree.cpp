#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
class LazySegtree {
private:
  const int sz;
  vector<T> tree;
  vector<T> lazy;

  /** applies lazy update to tree[v], places update at lazy[v] */
  void apply(int v, int len, T add)
  {
    tree[v] += add * len;
    lazy[v] += add;
  }

  /** pushes down lazy updates to children of v */
  void push_down(int v, int l, int r)
  {
    int m = (l + r) / 2;
    apply(2 * v, m - l + 1, lazy[v]);
    apply(2 * v + 1, r - m, lazy[v]);
    lazy[v] = 0;
  }

  void range_add(int v, int l, int r, int ql, int qr, int add)
  {
    if (qr < l || ql > r) {
      return;
    }
    if (ql <= l && r <= qr) {
      apply(v, r - l + 1, add);
    } else {
      push_down(v, l, r);
      int m = (l + r) / 2;
      range_add(2 * v, l, m, ql, qr, add);
      range_add(2 * v + 1, m + 1, r, ql, qr, add);
      tree[v] = tree[2 * v] + tree[2 * v + 1];
    }
  }

  T range_sum(int v, int l, int r, int ql, int qr)
  {
    if (qr < l || ql > r) {
      return 0;
    }
    if (ql <= l && r <= qr) {
      return tree[v];
    }
    push_down(v, l, r);
    int m = (l + r) / 2;
    return range_sum(2 * v, l, m, ql, qr) + range_sum(2 * v + 1, m + 1, r, ql, qr);
  }

public:
  LazySegtree(int n) : sz(n), tree(4 * n), lazy(4 * n)
  {
  }

  /** adds to every value on the range [ql, qr] */
  void range_add(int ql, int qr, int add)
  {
    range_add(1, 0, sz - 1, ql, qr, add);
  }

  /** @return sum of values on [ql, qr] */
  T range_sum(int ql, int qr)
  {
    return range_sum(1, 0, sz - 1, ql, qr);
  }
};

int main()
{
  int test_num;
  cin >> test_num;
  for (int t = 0; t < test_num; t++) {
    int n, q;
    cin >> n >> q;

    LazySegtree<ll> st(n);
    for (int i = 0; i < q; i++) {
      int type;
      cin >> type;

      if (type == 0) {
        int p, q, val;
        cin >> p >> q >> val;
        p--, q--;
        st.range_add(p, q, val);
      } else {
        int p, q;
        cin >> p >> q;
        p--, q--;
        cout << st.range_sum(p, q) << '\n';
      }
    }
  }
}