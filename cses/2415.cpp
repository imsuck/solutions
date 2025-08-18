#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/dbg.hpp"

#define all(a) begin(a), end(a)

using mint = modint107;

const int N = 5001;
mint fac[N], ifac[N], dp[N][N], pow_n[N], ipow_n[N];

void preprocess() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = i * fac[i - 1];
    ifac[N - 1] = fac[N - 1].inv();
    for (int i = N - 1; i >= 1; i--) ifac[i - 1] = i * ifac[i];

    dp[0][0] = 1;
    for (int n = 0; n + 1 < N; n++)
        for (int k = 1; k < N; k++) dp[n + 1][k] = n * dp[n][k] + dp[n][k - 1];
}
mint comb(int n, int k) {
    if (k < 0 || n < k) return 0;
    return fac[n] * ifac[n - k] * ifac[k];
}
mint _pow_n(int k) { return k < 0 ? ipow_n[-k] : pow_n[k]; }
mint forests(int n, int k) { return comb(n, k) * k * _pow_n(n - k - 1); }

// Pick a set R of vertices to be on any cycle
// These will also be the roots of some trees
// Let r = |R|
// Then the answer is stirling1(r, k)*comb(n, r)*r*n^(n-r-1)

void solve() {
    int n;
    cin >> n;
    pow_n[0] = 1;
    for (int i = 1; i < N; i++) pow_n[i] = n * pow_n[i - 1];
    ipow_n[N - 1] = pow_n[N - 1].inv();
    for (int i = N - 1; i >= 1; i--) ipow_n[i - 1] = n * ipow_n[i];

    for (int k = 1; k <= n; k++) {
        mint ans = 0;
        for (int r = k; r <= n; r++) ans += dp[r][k] * forests(n, r);
        cout << ans << "\n";
    }
}

int main() {
    preprocess();
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
