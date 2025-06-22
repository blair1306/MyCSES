#include <iostream>
#include <vector>
#include <numeric>

// Use a modern, type-safe approach for constants
const int M = 1e9 + 7;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of coin denominations
    int x; // Target sum
    std::cin >> n >> x;

    // Use std::vector for flexible array sizing
    std::vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> coins[i];
    }

    // dp[i] will store the number of ways to make sum i
    std::vector<int> dp(x + 1, 0);

    // **Correct Base Case:**
    // There is one way to make a sum of 0: by using no coins.
    dp[0] = 1;

    // Calculate the answer for each sum from 1 to x
    for (int i = 1; i <= x; i++)
    {
        // Try to form sum i using each available coin
        for (int c : coins)
        {
            // **Correct Condition:**
            // If the current sum 'i' is greater than or equal to the coin value 'c'
            if (i - c >= 0)
            {
                // The number of ways to form 'i' is the sum of ways of forming 'i' using other coins,
                // plus the number of ways of forming 'i - c' (to which we can add the coin 'c').
                // We use long long during addition to prevent potential overflow before the modulo.
                dp[i] = (dp[i] + dp[i - c]) % M;
            }
        }
    }

    // Output the final answer for the target sum x
    std::cout << dp[x] << std::endl;

    return 0;
}