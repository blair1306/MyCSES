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
const int N = 3000 + 5;  // size for global arrays (if needed)
#endif

char grid[N][N];

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    string result;
    queue<pii> q;
    q.push({0, 0});
    // int visited[N][N];
    result.push_back(grid[0][0]);
    vvi visited(n, vi(n));

    for (int step = 0; step < 2 * n - 2; step++) {
        vector<pii> next;
        char min_char = 'Z' + 1;
        dbg(q);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto [nx, ny] : {pair{x + 1, y}, pair{x, y + 1}}) {
                if (nx >= n || ny >= n || visited[nx][ny]) continue;
                visited[nx][ny] = 1;
                if (grid[nx][ny] <= min_char) {
                    if (grid[nx][ny] < min_char) next.clear();
                    min_char = grid[nx][ny];
                    next.push_back({nx, ny});
                }
            }
        }
        dbg(next);
        for (auto n : next) q.push(n);
        result.push_back(min_char);
    }

    cout << result << endl;

    return 0;
}