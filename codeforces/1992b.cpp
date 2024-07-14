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
    i32 n, k;
    cin >> n >> k;
    vec<i32> a(k);
    for (auto &i : a) {
        cin >> i;
    }
    sort(begin(a), end(a));
    i32 cnt = 0, ans = 0;
    for (int i = 0; i < k - 1; i++) {
        cnt += a[i];
        ans += a[i] - 1;
    }
    cout << ans + cnt << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}
