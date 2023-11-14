#include <iomanip>
#include <iostream>
using namespace std;

using i32 = int;
using f64 = double;

const i32 MAX = 3e3 + 69;

i32 n;
f64 ans = 0, p[MAX], dp[MAX][MAX];

inline f64 tail(f64 f) { return 1.0 - f; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << setprecision(12) << "\n";
    dp[0][0] = 1;

    cin >> n;
    for (i32 i = 1; i <= n; i++) {
        cin >> p[i];
    }

    for (i32 i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] * tail(p[i]);
        for (i32 j = 1; j <= i; j++) {
            dp[i][j] = dp[i - 1][j] * tail(p[i]) + dp[i - 1][j - 1] * p[i];
        }
    }
    for (i32 j = n / 2 + 1; j <= n; j++) {
        ans += dp[n][j];
    }

    cout << ans << "\n";
}
