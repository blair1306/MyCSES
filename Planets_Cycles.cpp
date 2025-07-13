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

using mii = unordered_map<int, int>;

vi G(N + 1);
vvi rG(N + 1);
vi vis(N + 1, 0);
vi dis(N + 1, 0);
vi in_cycle(N + 1, 0);
mii cycle_size;
vi comp(N + 1, 0);
int comp_id = 1;

void dfs(int u, int p)
{
    if (vis[u]) return;
    vis[u] = 1;
    comp[u] = comp_id;
    if (!in_cycle[u]) dis[u] = dis[p] + 1;

    for (auto v : rG[u]) {
        if (vis[v]) continue;
        dfs(v, u);
    }
}

void traverse(int u)
{
    vi path;
    mii m;
    int cycle_start_idx = u;
    path.push_back(u);
    m.insert({u, path.size() - 1});

    while (1) {
        u = G[u];
        if (m.count(u)) {
            cycle_start_idx = m[u];
            break;
        }
        path.push_back(u);
        m.insert({u, path.size() - 1});
    }

    cycle_size.insert({comp_id, path.size() - cycle_start_idx});
    for (int i = cycle_start_idx; i < path.size(); i++) {
        in_cycle[path[i]] = 1;
    }

    dfs(path[cycle_start_idx], -1);
    comp_id++;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        G[i] = b;
        rG[b].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) traverse(i);
    }

    dbg(comp);
    dbg(cycle_size);
    dbg(vis);
    dbg(dis);
    dbg(in_cycle);

    for (int i = 1; i <= n; i++) {
        int ans = -1;
        int cid = comp[i];
        ans = cycle_size[cid];
        if (!in_cycle[i]) {
            ans += dis[i];
        }
        cout << ans << " ";
    }

    cout << endl;

    return 0;
}