#include <bits/stdc++.h>
using namespace std;

template<class T> bool chmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    vector dp(a + 1, vector(b + 1, 1e9));
    for (int i = 1; i <= min(a, b); i++) dp[i][i] = 0;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            for (int k = 1; i - k >= 1; k++)
                chmin(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            for (int k = 1; j - k >= 1; k++)
                chmin(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
        }
    }
    cout << dp[a][b] << "\n";
}
