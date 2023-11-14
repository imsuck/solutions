#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<int>> value(n, vector<int>(3));
    vector<vector<int>> dp(n, vector<int>(3, 0));

    for (int i = 0; i < n; i++) {
        cin >> value[i][0];
        cin >> value[i][1];
        cin >> value[i][2];
    }
    dp[0][0] = value[0][0];
    dp[0][1] = value[0][1];
    dp[0][2] = value[0][2];

    for (int i = 1; i < n; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                if (j != k)
                    dp[i][j] = max(dp[i][j], dp[i - 1][k] + value[i][j]);

    cout << max(max(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]) << "\n";

    return 0;
}
