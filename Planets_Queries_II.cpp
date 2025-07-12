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

const int level = 31;

using si = unordered_set<int>;
using mii = map<int, int>;

int nxt[level][N];
vi pre[N];
int comp[N];  // id of component a node is in
int comp_id = 0;
vi dis(N, 0);        // distance to the cycle
vi cycle_id(N, -1);  // index in the cycle
mii cycle_size;      // cycle size of a component
bool in_cycle[N];
int vis[N];

void dfs(int u, int p, int cid)
{
    if (vis[u]) return;
    comp[u] = cid;
    vis[u] = 1;
    if (!in_cycle[u]) {
        dis[u] = dis[p] + 1;
    }

    for (auto v : pre[u]) {
        if (vis[v] || v == p) continue;
        dfs(v, u, cid);
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
        u = nxt[0][u];
        if (m.count(u)) {
            cycle_start_idx = m[u];
            dbg("cycle found");
            dbg(cycle_start_idx);
            dbg(path);
            break;
        }
        path.push_back(u);
        m.insert({u, path.size() - 1});
    }

    comp_id++;
    cycle_size[comp_id] = path.size() - cycle_start_idx;

    for (uint i = cycle_start_idx; i < path.size(); i++) {
        int u = path[i];
        cycle_id[u] = i - cycle_start_idx;
        in_cycle[u] = true;
    }

    dfs(path[cycle_start_idx], -1, comp_id);
}

int binary_lift(int u, int d)
{
    int v = u;
    for (int i = 0; i < level; i++) {
        if ((1 << i) & d) {
            v = nxt[i][v];
        }
    }

    return v;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        nxt[0][i] = b;
        pre[b].push_back(i);
    }

    dbg(pre);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            traverse(i);
        }
    }

    dbg(vis);
    dbg(in_cycle);
    dbg(cycle_id);
    dbg(cycle_size);
    dbg(dis);
    dbg(comp);

    for (int i = 1; i < level; i++) {
        for (int j = 1; j <= n; j++) {
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        }
    }

    dbg(comp);

    dbg(nxt);

    while (q--) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        int component = 0;
        if (a == b) {
            cout << 0 << endl;
            continue;
        }
        if (comp[a] != comp[b]) {
            cout << -1 << endl;
            continue;
        }
        component = comp[a];

        if (in_cycle[a] && in_cycle[b]) {
            if (cycle_id[b] > cycle_id[a]) {
                ans = cycle_id[b] - cycle_id[a];
            } else {
                ans = cycle_size[component] - cycle_id[a] + cycle_id[b];
            }
        } else if (in_cycle[a] && !in_cycle[b]) {
            ans = -1;
        } else if (in_cycle[b] && !in_cycle[a]) {
            ans = dis[a] + cycle_id[b];
        } else {
            if (dis[b] > dis[a]) {
                ans = -1;
            } else {
                int d = dis[a] - dis[b];
                if (b == binary_lift(a, d)) {
                    ans = d;
                } else
                    ans = -1;
            }
        }

        cout << ans << endl;
    }

    return 0;
}