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
    i32 n, tmp = -1, tot = -1, res = 1;
    cin >> n;
    i32 a[n + 1];

    for (i32 i = 1; i <= n; i++) {
        cin >> a[i];
        tot &= a[i];
    }
    if (tot != 0) {
        cout << "1\n";
        return;
    }
    for (i32 i = 1; i <= n; i++) {
        if (tmp == 0) {
            tmp = a[i];
        }
        tmp &= a[i];
        if (tmp == 0) {
            res++;
        }
    }
    cout << res - 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
