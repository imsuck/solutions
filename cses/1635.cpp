#include <bits/stdc++.h>
using namespace std;

const int mod = int(1e9 + 7);

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (int &i : c) cin >> i;

    vector<int> dp(x + 1);
    dp[0] = 1;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < n; j++) {
            if (i + c[j] > x) continue;
            (dp[i + c[j]] += dp[i]) %= mod;
        }
    }
    cout << dp[x] << "\n";
}
