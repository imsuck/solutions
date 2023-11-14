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
    i32 n, k, s = 0;
    cin >> n >> k;
    i32 a[n + 1], d[n + 1];
    a[0] = 0;
    for (i32 i = 1; i < n + 1; i++) {
        cin >> a[i];
        d[i] = abs(a[i] - a[i - 1]);
    }
    sort(d + 2, d + n + 1);
    for (i32 i = 2; i <= n - k + 1; i++) {
        s += d[i];
    }
    cout << s << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
