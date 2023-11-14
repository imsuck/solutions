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
    cin >> n;
    i32 l[10000] = {0};
    for (i32 i = 0; i < n; i++) {
        i32 a;
        cin >> a;
        l[a]++;
    }
    for (i32 i = 10000 - 1; i > 0; i--) {
        if (l[i] > l[i - 1]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
