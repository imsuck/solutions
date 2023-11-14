#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    int a[n];
    int dp[n];
    fill(dp, dp + n, 1e9);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dp[0] = 0;
    dp[1] = dp[0] + abs(a[0] - a[1]);

    for (int i = 2; i < n; i++)
        for (int j = k; j > 0; j--)
            if (0 <= i - j && i - j < n)
                dp[i] = min(dp[i], dp[i - j] + abs(a[i] - a[i - j]));

    cout << dp[n - 1] << "\n";

    return 0;
}
