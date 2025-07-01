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
const int N = 10 + 1;  // size for global arrays (if needed)
#else
const int N = 2e5 + 5;  // size for global arrays (if needed)
#endif

vvi T(N);
vi dis(N);

auto bfs(int s)
{
    int max_dis = 0;
    int farthest = -1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : T[u]) {
            if (dis[v] != INF) continue;
            dis[v] = 1 + dis[u];
            if (dis[v] > max_dis) {
                max_dis = dis[v];
                farthest = v;
            }
            q.push(v);
        }
    }

    return make_pair(max_dis, farthest);
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    T.resize(n + 1);

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        T[a].push_back(b);
        T[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) dis[i] = INF;
    dis[1] = 0;
    auto farthest = bfs(1);
    for (int i = 1; i <= n; i++) dis[i] = INF;
    dis[farthest.second] = 0;
    farthest = bfs(farthest.second);

    cout << farthest.first << endl;

    return 0;
}