#include <bits/stdc++.h>
using namespace std;

constexpr int M = 1000000007; // 10e9+7

int main()
{
    int n;
    int sum = 0;
    cin >> n;
    int sums[6] = {1, 2, 4, 8, 16, 32};

    if (n <= 6)
    {
        cout << sums[n - 1] << endl;
        return 0;
    }

    for (int i = 7; i <= n; i++)
    {
        sum = 0;
        for (int j = 0; j < 6; j++)
        {
            sum += sums[j];
            sum %= M;
        }
        sums[(i - 1) % 6] = sum;
    }

    cout << sum << endl;

    return 0;
}