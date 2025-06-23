#if defined(__APPLE__)
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

#elif defined(__linux__)
// Linux code
#include <bits/stdc++.h>
#else

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
const int N = 1000;      // size for global arrays (if needed)

int dp[N + 2][N + 2];

// Debugging (remove for submission)
#define DEBUG 0
#define dbg(...)                              \
    if (DEBUG)                                \
    {                                         \
        cerr << "[" << #__VA_ARGS__ << "]: "; \
        dbg_out(__VA_ARGS__);                 \
    }

void dbg_out() { cerr << '\n'; }

template <typename T, typename... Ts>
void dbg_out(T x, Ts... xs)
{
    cerr << x;
    if (sizeof...(xs))
        cerr << '\t';
    dbg_out(xs...);
}

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int h, w;
    char c;
    cin >> h >> w;
    pii start, end;

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            cin >> c;
            if (c == 'A')
            {
                start = {i, j};
                dp[i][j] = -3;
            }
            else if (c == 'B')
            {
                end = {i, j};
                dp[i][j] = -2;
            }
            else if (c == '#')
                dp[i][j] = -1;
            else
                dp[i][j] = -3;
        }
    }

    queue<pii> q;
    q.push(start);
    int d = 0;
    bool found = false;
    int qsize;
    while (true)
    {
        qsize = q.size();
        if (qsize == 0 || found)
            break;
        d++;
        for (int i = 0; i < qsize; i++)
        {
            int x, y;
            tie(x, y) = q.front();
            q.pop();
            if (dp[x][y] == -2)
            {
                found = true;
                break;
            }

            if (dp[x][y] == -1 || dp[x][y] != -3)
                continue;

            dp[x][y] = d;
            dbg(d, x, y);
            q.push({x + 1, y});
            q.push({x, y + 1});
            q.push({x - 1, y});
            q.push({x, y - 1});
        }
    }

    vector<char> dirs;

    d--; // wtf?
    if (found)
    {
        int x, y;
        tie(x, y) = end;
        while (d > 0)
        {
            if (dp[x - 1][y] == d)
            {
                dirs.push_back('D');
                x--;
            }
            else if (dp[x + 1][y] == d)
            {
                dirs.push_back('U');
                x++;
            }
            else if (dp[x][y - 1] == d)
            {
                dirs.push_back('R');
                y--;
            }
            else
            {
                dirs.push_back('L');
                y++;
            }
            dbg(d, x, y);
            d--;
        }
    }

    reverse(dirs.begin(), dirs.end());

    if (!found)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
        cout << dirs.size() << endl;
        for (auto c : dirs)
            cout << c;
        cout << endl;
    }

    return 0;
}