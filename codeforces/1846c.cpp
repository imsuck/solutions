#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long long;

void solve() {
    i32 n, m, h;
    cin >> n >> m >> h;
    i32 t[n][m];
    array<i32, 3> a[n];
    for (i32 i = 0; i < n; i++) {
        a[i][0] = 0;
    }
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            cin >> t[i][j];
        }
        sort(t[i], t[i] + m);
        a[i][2] = i;
    }
    for (i32 i = 0; i < n; i++) {
        i64 sum = 0, time = 0;
        for (i32 j = 0; j < m; j++) {
            time += t[i][j];
            sum += time;
            if (time <= h) {
                a[i][0]++;
                a[i][1] = sum;
            } else {
                break;
            }
        }
    }
    sort(a, a + n, [](const array<i32, 3> &a, const array<i32, 3> &b) {
        if (a[0] == b[0]) {
            if (a[1] == b[1]) {
                return a[2] < b[2];
            }
            return a[1] < b[1];
        }
        return a[0] > b[0];
    });
    for (i32 i = 0; i < n; i++) {
        if (a[i][2] == 0) {
            cout << i + 1 << "\n";
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
