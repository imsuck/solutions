// IDK knapsack so no AC
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, mx = 0, total = 0;
    cin >> n;
    int a[n + 1], dp[n + 1];
    fill(dp, dp + n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total += a[i];
    }
    int mid = total / 2;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] + a[i] < mid) {
                dp[i] = max(dp[i], dp[j] + a[i]);
                mx = max(mx, dp[i]);
            } else if (dp[j] + a[i] == mid) {
                cout << total - 2 * mid << "\n";
                return 0;
            }
        }
    }

    cout << total - 2 * mx << "\n";

    return 0;
}
