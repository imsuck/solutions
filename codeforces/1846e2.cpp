#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define vec vector
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

set<u64> ans;

void build() {
    for (u64 i = 2; i <= 1e6; i++) {
        u64 s = 1 + i;
        u64 k = i * i;
        for (u64 p = 3; p <= 63; p++) {
            s += k;
            if (s > 1e18) {
                break;
            }
            ans.insert(s);
            if (k > i64(1e18) / i) {
                break;
            }
            k *= i;
        }
    }
}

void solve() {
    u64 n;
    cin >> n;
    if (ans.count(n)) {
        cout << "YES\n";
        return;
    }
    i64 d = 4 * n - 3;
    i64 sqrt_d = sqrt(f128(d));
    if (sqrt_d > 3 && sqrt_d * sqrt_d == d && sqrt_d % 2 != 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    build();
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
