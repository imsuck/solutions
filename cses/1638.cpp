#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using str = string;
template <class T> using vec = vector<T>;
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

const i32 MOD = 1e9 + 7;

void solve() {
    i32 n;
    cin >> n;
    i32 dp[n + 1][n + 1];
    for (i32 i = 0; i <= n; i++) {
        for (i32 j = 0; j <= n; j++) {
            dp[i][j] = 0;
        }
    }
    dp[1][1] = 1;
    for (i32 i = 1; i <= n; i++) {
        for (i32 j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == '.') {
                dp[i][j] += (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            } else {
                dp[i][j] = 0;
            }
        }
    }
    cout << dp[n][n] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    while (t--)
        solve();
}
