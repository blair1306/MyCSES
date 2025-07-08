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
const int N = 1e7 + 5;  // size for global arrays (if needed)
#endif

int trie[N][26];    // there'are 26 letters dumb ass! not 24;
int isLeaf[N];
int cnt = 0;

int main()
{
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    string p;
    cin >> p;
    int k;

    cin >> k;
    for (int i = 0; i < k; i++) {
        string word;
        cin >> word;
        int cur = 0;
        for (auto c : word) {
            uint num = c - 'a';
            if (!trie[cur][num]) {
                trie[cur][num] = ++cnt;
            }
            cur = trie[cur][num];
        }
        isLeaf[cur] = 1;
    }

    dbg(cnt, trie);
    dbg(isLeaf);

    vi dp(p.size() + 1, 0);
    dp[0] = 1;

    for (uint i = 0; i < p.size(); i++) {
        if (dp[i] == 0) continue;
        int cur = 0;
        for (uint j = i; j < p.size(); j++) {
            int c = p[j] - 'a';
            if (!trie[cur][c]) break;
            cur = trie[cur][c];
            if (isLeaf[cur]) dp[j + 1] = (dp[i] + dp[j + 1]) % MOD;
        }
    }

    dbg(dp);

    cout << dp[p.size()] << endl;

    return 0;
}