#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

const int M = 1e9 + 7;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int x;

    cin >> n >> x;

    vpii book(n, {0, 0});

    for (int i = 0; i < n; i++)
        cin >> book[i].first;

    for (int i = 0; i < n; i++)
        cin >> book[i].second;

    vi dp(x + 1, 0);

    /*
    If you update from low to high →
    "dp[j - h_i]" might already include this book →
    allows taking it multiple times →
    becomes unbounded knapsack.
    */

    for (auto b : book)
    {
        int price = b.first;
        int npage = b.second;

        for (int i = x; i >= price; i--)
        {
            dp[i] = max(dp[i], dp[i - price] + npage);
        }
    }

    cout << dp.at(x);

    return 0;
}