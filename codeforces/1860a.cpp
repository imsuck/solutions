#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
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

bool contains(str a, str b) {
    for (i32 i = 0; i < a.len(); i++) {
        if (b == a.substr(i, b.len())) {
            return true;
        }
    }
    return false;
}

void solve() {
    str s, ans = "";
    cin >> s;
    for (i32 i = 0; i < s.len(); i++) {
        ans += "()";
    }
    if (contains(ans, s)) {
        ans = string(s.len(), '(') + string(s.len(), ')');
        if (contains(ans, s)) {
            cout << "NO\n";
            return;
        } else {
            cout << "YES\n";
        }
    } else {
        cout << "YES\n";
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
