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
typedef pair<int, int> pi;
typedef vector<pi> vpi;
typedef long long ll;

const int M = 1e9 + 7;
const int N = 1000 + 1;

int dp[N][N];

#define foreach(i, n) for (int i = 0; i < n; i++)
#define DEBUG 1

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n1 = 0;
    int n2 = 0;

    cin >> n1 >> n2;
    if (n1 < n2)
        swap(n1, n2);
    vi i1(n1);
    vi i2(n2);

    foreach (i, n1)
        cin >> i1[i];
    foreach (i, n2)
        cin >> i2[i];

    int max_len = 0;

    foreach (i, n1)
    {
        foreach (j, n2)
        {
            if (i1[i] != i2[j])
                continue;
            if (max_len == 0 && ++max_len)
                dp[max_len][i] = 1;
            else
            {
                int len = max_len;
                bool found = false;

                while (len > 0 && !found)
                {
                    for (int k = 0; k < n1 && !found; k++)
                    {
                        if (dp[len][k] != 0)
                            continue;
                        if (i > k)
                        {
#if DEBUG
                            cout << "i:" << i << endl;
#endif
                            dp[len + 1][i] = 1;
                            found = true;
                            if (len == max_len)
                                max_len++;
                        }
                        if (len == 1)
                        {
                            dp[1][i] = 1;
                            found = true;
                        }
                        len--;
                    }
                }
            }
        }
    }

    vi ans;
    int last = INT_MAX;
    for (int i = max_len; i > 0; i--)
    {
        for (int j = n1 - 1; j >= 0; j--)
        {
            if (dp[i][j] && last > j)
            {
                last = j;
                ans.push_back(i1[j]);
                break;
            }
        }
    }

    cout << max_len << endl;
    reverse(ans.begin(), ans.end());
    for (auto i : ans)
        cout << i << " ";
    cout << endl;

    return 0;
}
