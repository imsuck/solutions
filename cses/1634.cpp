#include <bits/stdc++.h>
using namespace std;

const int INF = 2e6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    int coins[n];

    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    int dp[x + 3];
    int trace[x + 3];
    dp[0] = 0;

    for (int i = 1; i <= x; i++) {
        dp[i] = INF;
        for (int coin : coins) {
            if (i - coin >= 0) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    if (dp[x] != INF) {
        cout << dp[x] << "\n";
    } else
        cout << "-1\n";

    return 0;
}
