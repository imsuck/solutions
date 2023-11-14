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
    i64 n, k, g, res = 0;
    cin >> n >> k >> g;
    i64 x = (g + 1) / 2 - 1;
    res += x * (n - 1);
    i64 y = k * g - res;
    cout << y << " " << y % g << "\n";
    res += y % g;
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
