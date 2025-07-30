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

const int BOARD_LEN = 6;
const int BOARD_SIZE = BOARD_LEN * BOARD_LEN;

struct Point {
    Point(int _x, int _y) : x(_x), y(_y) {};
    int x;
    int y;
};

const Point dirs[] = {Point(-2, 1), Point(2, 1),  Point(2, -1), Point(-2, -1),
                      Point(1, 2),  Point(-1, 2), Point(1, -2), Point(-1, -2)};
int board[BOARD_LEN][BOARD_LEN];

using pip = pair<int, Point>;
using vpip = vector<pip>;

vpip getAvailableMoves(Point u, int depth = 1)
{
    vpip moves;
    vpip tmp;
    for (auto [dx, dy] : dirs) {
        int numNextMove = 0;
        Point v = Point(u.x + dx, u.y + dy);
        if (v.x < 0 || v.y < 0) continue;
        if (v.x >= BOARD_LEN || v.y >= BOARD_LEN) continue;
        if (board[v.x][v.y] != 0) continue;
        if (depth) {
            tmp = getAvailableMoves(v, depth - 1);
            numNextMove = tmp.size();
        }
        moves.push_back({numNextMove, v});
    }

    sort(all(moves), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });
    // for (auto [num, move] : moves) {
    //     cout << num << ",";
    // }
    // cout << endl;
    return moves;
}

bool dfs(Point u, int cnt)
{
    if (cnt > BOARD_SIZE) return true;
    for (auto [s, v] : getAvailableMoves(u)) {
        board[v.x][v.y] = cnt;
        if (dfs(v, cnt + 1)) return true;
        board[v.x][v.y] = 0;
    }

    return false;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int x, y;
    cin >> x >> y;
    swap(x, y);
    x--;
    y--;

    board[x][y] = 1;
    dfs(Point(x, y), 2);

    for (int i = 0; i < BOARD_LEN; i++) {
        for (int j = 0; j < BOARD_LEN; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}