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

const i32 MOD = 998244353;
const i64 INF = numeric_limits<i64>::max();

struct S {
    i64 a, b;
    S() : a{}, b{} {}
    S(i64 a, i64 b) : a{a}, b{b} {}
};

void solve() {
    i32 n;
    cin >> n;
    vec<i32> v(n);
    for (i32 &i : v) cin >> i;

    S mn{v[0], 1}, mx{abs(v[0]), 1};
    cout << "0 " << mn.b << " " << mx.b << "\n";
    for (i32 i = 1; i < n; i++) {
        S t1, t2;
        t1.a = mn.a + v[i];
        t1.b = mn.b * (mn.a != mx.a && mn.a + v[i] >= 0 ? 2 : 1);
        if (mx.a + v[i] <= t1.a) {
            t1.a = mx.a + v[i];
            if (mx.a + v[i] < t1.a) t1.b = 0;
            t1.b += mx.b * (mn.a != mx.a && mx.a + v[i] >= 0 ? 2 : 1);
        }
        t2.a = abs(mx.a + v[i]);
        t2.b = mx.b * (mn.a != mx.a && mx.a + v[i] >= 0 ? 2 : 1);
        if (abs(mn.a + v[i]) >= t2.a) {
            t2.a = abs(mn.a + v[i]);
            if (abs(mn.a + v[i]) > t2.a) t2.a = 0;
            t2.b += mn.b * (mn.a != mx.a && mn.a + v[i] >= 0 ? 2 : 1);
        }
        mn = t1, mx = t2;
        cout << i << " " << mn.b << " " << mx.b << "\n";
    }

    cout << mx.b << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}
