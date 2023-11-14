#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using str = string;
#define vec vector

void solve() {
    i32 n;
    f64 d, h;
    cin >> n >> d >> h;
    f64 b = d / 2, triag_a = b * h, area = triag_a;
    f64 y[n];
    for (i32 i = 0; i < n; i++) {
        cin >> y[i];
    }
    for (i32 i = 1; i < n; i++) {
        f64 h1 = max(y[i - 1] - y[i] + h, 0.0);
        f64 b1 = h1 / h * b;
        area += b * h - h1 * b1;
    }
    cout << area << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(20);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
