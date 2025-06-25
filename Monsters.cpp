#if defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>
#endif

// #define LOCAL
#ifdef LOCAL
#include "mydebug.h"
#else
#define dbg(...)
#define dbg_arr(...)
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

// Constants
const int INF = 1e9 + 5;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; // or 998244353
#ifdef LOCAL
const int N = 10;
#else
const int N = 1e3; // size for global arrays (if needed)
#endif

struct pos
{
    int x;
    int y;
};

pos dir[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // "U" "D" "L" "R"
char dir_str[4] = {'U', 'D', 'L', 'R'};
char rev_dir_str[4] = {'D', 'U', 'R', 'L'};

int dis[N][N];
char labyr[N][N];
int visited[N][N];

int n, m;
#define valid(x, y) (x >= 0 && x < n && y >= 0 && y < m)

void bfs(vector<pos> s)
{
    queue<pos> q;
    for (pos i : s)
    {
        visited[i.x][i.y] = true;
        dis[i.x][i.y] = 0;
        q.push(i);
    }
    int len = 1;
    while (!q.empty())
    {
        int qsize = q.size();
        for (int i = 0; i < qsize; i++)
        {
            pos u = q.front();
            q.pop();

            for (auto d : dir)
            {
                // dbg(labyr);
                pos v = {u.x + d.x, u.y + d.y};
                if (!valid(v.x, v.y))
                    continue;
                if (visited[v.x][v.y])
                    continue;
                if (labyr[v.x][v.y] == '#')
                    continue;
                visited[v.x][v.y] = true;
                dis[v.x][v.y] = len;
                // dbg(labyr);
                q.push({v.x, v.y});
            }
        }
        len++;
    }
}

vector<char> backtrace(pos start, int distance)
{
    vector<char> route;
    dbg(dis);
    while (--distance > -1)
    {
        pos v;
        for (int i = 0; i < 4; i++)
        {
            v = {start.x + dir[i].x, start.y + dir[i].y};
            if (valid(v.x, v.y))
            {
                if (dis[v.x][v.y] == distance)
                {
                    route.push_back(rev_dir_str[i]);
                    break;
                }
            }
        }
        start.x = v.x;
        start.y = v.y;
    }
    reverse(all(route));
    return route;
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    cin >> n >> m;

    vector<pos> monster;
    pos player;
    vector<pos> exit; //

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            labyr[i][j] = c;
            if (c == 'A')
            {
                player = {i, j};
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
                {
                    cout << "YES" << endl;
                    cout << 0 << endl;
                    return 0;
                }
            }
            if (c == 'M')
            {
                monster.push_back({i, j});
            }
            if (c == '.' && (i == 0 || j == 0 || i == n - 1 || j == m - 1))
            {
                exit.push_back({i, j});
            }
        }
    }

    vi my_distance;
    vi monster_distance;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = 0;
            dis[i][j] = INF;
        }

    bfs(monster);
    for (auto e : exit)
    {
        monster_distance.push_back(dis[e.x][e.y]);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = 0;
            dis[i][j] = INF;
        }
    bfs({player});

    for (auto e : exit)
    {
        my_distance.push_back(dis[e.x][e.y]);
    }

    for (auto i = 0; i < my_distance.size(); i++)
    {
        if (my_distance[i] >= monster_distance[i])
            continue;
        // backtrace

        auto route = backtrace(exit[i], my_distance[i]);

        cout << "YES" << endl;
        cout << route.size() << endl;
        for (auto c : route)
            cout << c;
        cout << endl;
        return 0;
    }

    cout << "NO" << endl;

    return 0;
}
