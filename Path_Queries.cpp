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
class FenwickTree {
public:
    FenwickTree(size_t n) : size(n), arr(n + 1) {};
    T query(int idx)
    {
        T ans = 0;
        for (; idx > 0; idx -= (idx & -idx)) {
            ans += arr[idx];
        }
        return ans;
    }
    void update(int idx, T dt)
    {
        for (; (size_t)idx <= size; idx += (idx & -idx)) {
            arr[idx] += dt;
        }
    }

private:
    size_t size;
    vector<T> arr;
};

int timer = 1;
vi pos_id(N, -1);
vector<pii> pos(N);
vi tree[N];

void dfs(int u, int p)
{
    pos[u].first = timer++;
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    pos[u].second = timer - 1;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vi vals(n + 1);
    for (int i = 1; i <= n; i++) cin >> vals[i];

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, -1);

    FenwickTree<ll> ft(n);
    for (int i = 1; i <= n; i++) {
        auto [start, end] = pos[i];

        ft.update(start, vals[i]);
        ft.update(end + 1, -vals[i]);
    }

    while (q--) {
        int t, s;
        ll x;
        cin >> t >> s;
        auto [start, end] = pos[s];

        if (t == 2) {
            ll psum = ft.query(start);
            cout << psum << endl;
        }
        if (t == 1) {
            cin >> x;
            ll dt = x - vals[s];
            vals[s] = x;
            ft.update(start, dt);
            ft.update(end + 1, -dt);
        }
    }

    return 0;
}