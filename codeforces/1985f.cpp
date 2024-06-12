#include <algorithm>
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

const i64 MAX_TIME = i64(2e5 * 2e5);

template<class T> T ceil_div(T a, T b) { return (a + b - 1) / b;}

void solve() {
    i32 h, n;
    cin >> h >> n;
    vec<i64> a(n), c(n);
    for (auto &i : a) cin >> i;
    for (auto &i : c) cin >> i;
    auto check = [&](i64 time) {
        i64 sum = 0;
        for (int i = 0; i < n; i++) {
            sum += ceil_div(time, c[i]) * a[i];
            if (sum >= h) return true;
        }
        return false;
    };
    i64 l = 0, r = MAX_TIME + 1;
    while (r - l > 1) {
        i64 m = r - (r - l) / 2;
        if (!check(m)) 
            l = m;
        else
            r = m;
    }
    cout << r << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}
