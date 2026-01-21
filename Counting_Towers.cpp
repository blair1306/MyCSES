#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef long long ll;

const int M = 1e9 + 7;
const int N = 1e6;

ll dp[N + 1][2];

int main()
{
  // Fast I/O
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int t;
  cin >> t;
  int n;

  // pre-compute the dp matrix
  /*
      dp[x][0] number of ways when at x level we have two tiles of width 1
      dp[x][1] ...... width 2

      |_| |_|
      |_| |_|

      | | | |
      |_| |_|

      |_| | |
      |_| |_|

      | | |_|
      |_| |_|
  */
  dp[1][0] = 1;
  dp[1][1] = 1;

  for (int i = 2; i <= N; i++) {
    dp[i][0] = (4 * dp[i - 1][0]) % M + dp[i - 1][1];
    dp[i][1] = dp[i - 1][0] + (2 * dp[i - 1][1]) % M;
    dp[i][0] %= M;
    dp[i][1] %= M;
  }

  int ans = 0;

  for (int i = 0; i < t; i++) {
    cin >> n;
    ans = dp[n][0] + dp[n][1];
    ans %= M;
    cout << ans << endl;
  }

  return 0;
}