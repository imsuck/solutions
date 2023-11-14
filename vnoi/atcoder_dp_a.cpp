#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int a[n];
    int dp[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dp[0] = 0;
    dp[1] = dp[0] + abs(a[0] - a[1]);

    for (int i = 2; i < n; i++) {
        dp[i] = min(dp[i - 1] + abs(a[i] - a[i - 1]),
                    dp[i - 2] + abs(a[i] - a[i - 2]));
    }

    cout << dp[n - 1] << "\n";

    return 0;
}
