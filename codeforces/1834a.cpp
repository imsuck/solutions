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
    i32 n, cnt = 0;
    cin >> n;
    for (i32 i = 0; i < n; i++) {
        i32 a;
        cin >> a;
        if (a == -1)
            cnt++;
    }
    i32 mid = n / 2;
    mid -= mid % 2;
    cout << max(cnt - mid, 0) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
