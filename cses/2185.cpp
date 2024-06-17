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

void solve() {
    i64 n;
    i32 k;
    cin >> n >> k;
    vec<i64> p(k);
    for (auto &i : p) cin >> i;

    i64 res = 0;

    auto sg = [](i64 a) -> i64 { return a & 1 ? 1 : -1; };

    for (i32 i = 1; i < i64(1) << k; i++) {
        bool ok = true;
        i64 prod = 1;
        for (i32 j = 0; j < k; j++) {
            if ((i >> j & 1) == 0) continue;
            if (prod > n / p[j]) {
                ok = false;
                break;
            }
            prod *= p[j];
        }
        if (ok) res += sg(__builtin_popcount(i)) * n / prod;
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}
