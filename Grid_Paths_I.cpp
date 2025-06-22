#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    char c;

    vvi grid(n + 1, vi(n + 1, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> c;
            if (c == '*')
            {
                grid[i + 1][j + 1] = -1;
            }
        }
    }

    if (grid[1][1] == -1)
    {
        cout << 0;
        return 0;
    }

    grid[1][1] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i + j == 2)
                continue;
            if (grid[i - 1][j] == -1 && grid[i][j - 1] == -1)
                continue;
            if (grid[i][j] == -1)
                continue;

            int v = 0;
            if (grid[i - 1][j] == -1)
                v = grid[i][j - 1];
            else if (grid[i][j - 1] == -1)
                v = grid[i - 1][j];
            else
                v = grid[i - 1][j] + grid[i][j - 1];

            grid[i][j] = v % M;
        }
    }

    int ans = grid[n][n];
    if (ans == -1)
        ans = 0;

    cout << ans;

    return 0;
}