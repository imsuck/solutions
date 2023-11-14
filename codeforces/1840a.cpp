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
    int n;
    cin >> n;
    str s, ans = "";
    cin >> s;
    char start = s[0];
    for (int i = 1; i < n; i++) {
        if (s[i] == start) {
            ans += s[i];
            if (i + 1 < n) {
                start = s[i + 1];
                i += 1;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
