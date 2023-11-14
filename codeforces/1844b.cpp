#include <bits/stdc++.h>
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
using ui128 = __uint128_t;
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
    if (n == 1) {
        cout << "1\n";
        return;
    } else if (n == 2) {
        cout << "1 2\n";
        return;
    }
    i32 c = 4;
    for (i32 i = 0; i < n; i++) {
        if (i == 0) {
            cout << "2 ";
        } else if (i == n / 2) {
            cout << "1 ";
        } else if (i == n - 1) {
            cout << "3 ";
        } else {
            cout << c << " ";
            c++;
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
