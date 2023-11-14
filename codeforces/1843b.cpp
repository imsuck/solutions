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
    i64 n, res = 0, cnt = 0;
    cin >> n;
    i64 a[n];
    for (i32 i = 0; i < n; i++) {
        cin >> a[i];
        res += abs(a[i]);
    }

    for (i32 i = 0; i < n; i++) {
        if (a[i] < 0) {
            for (i32 j = i; j < n; j++) {
                if (a[j] > 0 || j == n - 1) {
                    i = j;
                    cnt++;
                    break;
                }
            }
        }
    }

    cout << res << " " << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
