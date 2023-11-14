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
    i32 n;
    cin >> n;
    vec<i32> a(n), b, c;
    for (i32 &x : a) {
        cin >> x;
    }
    i32 mx = *max_element(all(a));
    for (i32 x : a) {
        if (x != mx) {
            b.eb(x);
        } else {
            c.eb(x);
        }
    }
    if (b.empty()) {
        cout << "-1\n";
        return;
    }
    cout << b.len() << " " << c.len() << "\n";
    for (i32 x : b) {
        cout << x << " ";
    }
    cout << "\n";
    for (i32 x : c) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
