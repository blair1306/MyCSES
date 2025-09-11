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
// #ifdef LOCAL
// const int N = 10;  // size for global arrays (if needed)
// #else
// const int N = 2e5 + 5;  // size for global arrays (if needed)
// #endif

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

template <class T>
class BIT {
    static_assert(is_arithmetic<T>::value, "Number required");

private:
    const size_t N;
    vector<T> data;

public:
    BIT() : N(0) {};
    BIT(const size_t _N) : N(_N), data(_N + 1) {};

    size_t size()
    {
        return N;
    }

    T sum(size_t idx)
    {
        T ans = 0;
        for (; idx > 0; idx -= (idx & -idx)) {
            dbg(idx);
            ans += data[idx];
        }
        return ans;
    }
    T sum(size_t l, size_t r)
    {
        return sum(r) - sum(l - 1);
    }

    void add(size_t idx, T val)
    {
        for (; idx <= N; idx += (idx & -idx)) {
            dbg(idx);
            data[idx] += val;
        }
    }
};

const int MAXN = 2e5;

int N, Q;
vector<int> adj[MAXN];
int labels[MAXN];
int sz[MAXN];
int values[MAXN];

void dfs(int i, int par, int& label)
{
    labels[i] = label;
    label++;
    for (int j : adj[i]) {
        if (j == par) continue;
        dfs(j, i, label);
        sz[i] += sz[j];
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // freopen("input.txt", "r", stdin);

    cin >> N >> Q;
    for (int i = 0; i < N; ++i) {
        cin >> values[i];
    }
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int temp = 1;
    fill(sz, sz + N, 1);
    dfs(0, -1, temp);

    BIT<ll> bit(N + 1);
    for (int i = 0; i < N; ++i) {
        bit.add(labels[i], values[i]);
        bit.add(labels[i] + sz[i], -values[i]);
    }

    for (int i = 0; i < Q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, v;
            cin >> a >> v;
            a--;
            bit.add(labels[a], -values[a] + v);
            bit.add(labels[a] + sz[a], values[a] - v);
            values[a] = v;
        } else {
            int b;
            cin >> b;
            b--;
            cout << bit.sum(labels[b]) << '\n';
        }
    }
}
