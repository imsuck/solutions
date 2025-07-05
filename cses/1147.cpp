#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;
template<class T> using vec = vector<T>;

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<str> b(n);
    for (auto &s : b) cin >> s;

    i32 ans = 0;
    vec<i32> d(m + 1);
    d[m] = -1;
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) d[j] = b[i][j] == '*' ? 0 : d[j] + 1;
        stack<i32> s;
        s.push(-1);
        for (i32 j = 0; j <= m; j++) {
            while (s.size() > 1 && d[s.top()] >= d[j]) {
                i32 x = d[s.top()];
                s.pop();
                ans = max(ans, (j - s.top() - 1) * x);
            }
            s.push(j);
        }
    }
    cout << ans << "\n";
}

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}
