#include "bits/stdc++.h"
using namespace std;

ostream cnull(nullptr);
#ifndef LOCAL
#define cerr cnull
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i64 n, c;
    cin >> n >> c;
    i128 sum = 0, soq = 0;
    for (i32 i = 0; i < n; i++) {
        i64 a;
        cin >> a;
        sum += a;
        soq += i128(a * a);
    }
    i64 w = (-sum + sqrtl(sum * sum - soq * n + (i128)n * c)) / (2 * n);
    cout << w << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
