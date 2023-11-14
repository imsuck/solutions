#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int prev_sum(int arr[], int idx, int size) {
    int res = 0;
    for (int i = idx - 6; i < idx && i < size; i++) {
        if (i <= 0)
            continue;
        res += arr[i];
        res %= MOD;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int dp[n + 3];
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = prev_sum(dp, i, n + 3) % MOD;
        if (i <= 6)
            dp[i]++;
        dp[i] %= MOD;
    }

    cout << dp[n] << "\n";

    return 0;
}
