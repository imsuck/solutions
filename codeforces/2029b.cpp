#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) 42
    #define mark_dbg() if (false)
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f80 = long double;
using str = string;
template<class T> using vec = vector<T>;
template<class T> int len(T &&x) { return int(x.size()); }
#define all(a) begin(a), end(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n;
    cin >> n;
    str s, r;
    cin >> s >> r;

    i32 c0 = 0, c1 = 0;
    for (char c : s) c == '0' ? c0++ : c1++;

    if (s == str(len(s), '0') || s == str(len(s), '1')) {
        cout << "no\n";
        return;
    }

    for (char c : r) {
        if (c == '0') {
            c1--;
        } else {
            c0--;
        }
        if ((c0 < 1 || c1 < 1) && c0 + c1 != 1) {
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}
