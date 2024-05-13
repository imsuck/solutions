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
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n;
    cin >> n;
    vec<i32> x(n), a(n);
    for (i32 i = 1; i < n; i++) {
        cin >> x[i];
    }
    a[0] = x[1] + 1, a.back() = x.back();
    for (i32 i = 1; i + 1 < n; i++) {
        i32 k = x[i + 1] / a[i - 1] + 1;
        // while (k * a[i-1] + x[i] <= a[i + 1])
        //     k++;
        // while ((k-1) * a[i-1] + x[i] > a[i + 1])
        //     k--;
        a[i] = k * a[i - 1] + x[i];
    }
    for (i32 i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n-1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}
