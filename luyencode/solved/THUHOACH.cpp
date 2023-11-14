#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    cin >> n >> c;
    int w[n + 1], dp[n + 1][c + 1];
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int i = 0; i <= c; i++)
        dp[0][i] = 0;

    for (int i = 1; i <= n; i++)
        cin >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= c; j++)
            dp[i][j] =
                max(dp[i - 1][j], j >= w[i] ? dp[i - 1][j - w[i]] + w[i] : 0);

    cout << dp[n][c] << "\n";

    return 0;
}
