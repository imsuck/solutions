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
    char a[4][4];
    for (i32 i = 1; i <= 3; i++) {
        for (i32 j = 1; j <= 3; j++) {
            cin >> a[i][j];
        }
    }
    for (i32 i = 1; i <= 3; i++) {
        if (a[i][1] != '.' && a[i][1] == a[i][2] && a[i][2] == a[i][3]) {
            cout << a[i][1] << "\n";
            return;
        }
        if (a[1][i] != '.' && a[1][i] == a[2][i] && a[2][i] == a[3][i]) {
            cout << a[1][i] << "\n";
            return;
        }
    }
    if (a[1][1] != '.' && a[1][1] == a[2][2] && a[2][2] == a[3][3]) {
        cout << a[1][1] << "\n";
    } else if (a[1][3] != '.' && a[1][3] == a[2][2] && a[2][2] == a[3][1]) {
        cout << a[1][3] << "\n";
    } else {
        cout << "DRAW\n";
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
