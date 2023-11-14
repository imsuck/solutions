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
    i64 res = 0;
    cin >> n;
    i32 a[n];
    for (i32 i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    for (i32 i = 0; i < n / 2; i++) {
        res += a[n - i - 1] - a[i];
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
