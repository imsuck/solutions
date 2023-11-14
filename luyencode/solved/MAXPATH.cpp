#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long m, n;
    long long res = -1e7;
    cin >> m >> n;
    long long a[m][n], dp[m][n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
        dp[i][0] = a[i][0];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < m; i++) {
            dp[i][j] = -1e7;
            if (i - 1 >= 0 && dp[i][j] < dp[i - 1][j - 1] + a[i][j])
                dp[i][j] = dp[i - 1][j - 1] + a[i][j];
            if (dp[i][j] < dp[i][j - 1] + a[i][j])
                dp[i][j] = dp[i][j - 1] + a[i][j];
            if (i + 1 < m && dp[i][j] < dp[i + 1][j - 1] + a[i][j])
                dp[i][j] = dp[i + 1][j - 1] + a[i][j];

            if (j == n - 1)
                res = max(res, dp[i][j]);
        }
    }

    cout << res << "\n";

    return 0;
}
