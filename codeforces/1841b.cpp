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
    i32 q;
    cin >> q;
    i32 prev = -1;
    i32 start = -1;
    bool b = false;
    for (i32 i = 0; i < q; i++) {
        i32 x;
        cin >> x;
        if (i == 0) {
            cout << '1';
            start = prev = x;
        } else if (((prev <= x && (!b || x <= start)) || (!b && x <= start))) {
            if (prev > x)
                b = true;
            cout << '1';
            prev = x;
        } else {
            cout << '0';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
