#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

const i32 MOD = 1e9 + 7;

void solve() {
    i32 n, m;
    cin >> n >> m;
    vec<i64> fac(n + m, 1);
    for (int i = 2; i < n + m; i++) fac[i] = fac[i - 1] * i % MOD;
    auto pow = [](i64 a, i64 n) {
        i64 res = 1;
        while (n) {
            if (n & 1) res = res * a % MOD;
            a = a * a % MOD;
            n >>= 1;
        }
        return res;
    };
    auto comb = [&](i64 n, i64 k) -> i64 {
        if (n < k) return 0;
        return fac[n] * pow(fac[k], MOD - 2) % MOD * pow(fac[n - k], MOD - 2) % MOD;
    };
    cout << comb(n + m - 1, n - 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}
