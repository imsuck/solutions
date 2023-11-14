#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, max_len = 0;
    cin >> n;
    int a[n], dp[n];
    fill(dp, dp + n, 1);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1);
        max_len = max(max_len, dp[i]);
    }

    cout << max_len << "\n";

    return 0;
}
