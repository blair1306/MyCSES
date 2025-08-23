#if defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
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

template <class T>
class SegmentTree {
    using Arr = vector<T>;
    Arr arr;
    Arr vals;
    uint size;

public:
    SegmentTree(Arr &vals) : vals(vals), size(1)
    {
        build();
    };

    void build()
    {
        while (size <= vals.size()) size <<= 1;
        arr.resize(2 * size);
        for (uint i = 0; i < vals.size(); i++) arr[i + size] = vals[i];
        for (int i = size - 1; i > 0; i--) {
            arr[i] = arr[i << 1] + arr[i << 1 | 1];
        }
        dbg(arr);
    }

    void update(int u, T val)
    {
        T delta = val - vals[u];
        vals[u] = val;
        u += size;
        arr[u] += delta;

        for (u >>= 1; u > 0; u >>= 1) {
            arr[u] = arr[u << 1] + arr[u << 1 | 1];
        }
    }

    T query(int left, int right)
    {
        T res = 0;
        for (left += size, right += size; left <= right; left >>= 1, right >>= 1) {
            if (left & 1) res += arr[left++];
            if (!(right & 1)) res += arr[right--];
        }

        return res;
    }
};

vi start_pos(N);
vi end_pos(N);
vi tree[N];
int cnt = 0;

void dfs(int u, int p)
{
    start_pos[u] = ++cnt;
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    end_pos[u] = cnt;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    vll arr;
    cin >> n >> q;
    arr.resize(n);
    for (auto &a : arr) cin >> a;

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0);
    dbg(start_pos);
    dbg(end_pos);

    SegmentTree<ll> segtree(arr);

    while (q--) {
        int t, a, val;
        cin >> t;
        if (t == 1) {
            cin >> a >> val;
            segtree.update(--a, val);
        }
        if (t == 2) {
            ll ans;
            int left, right;
            cin >> a;
            left = start_pos[a];
            right = end_pos[a];
            ans = segtree.query(--left, --right);
            cout << ans << endl;
        }
    }

    return 0;
}