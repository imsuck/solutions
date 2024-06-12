#include <bits/stdc++.h>
#include <numeric>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n;
    cin >> n;
    vec<i64> v(n);
    set<i64> s;
    i32 cnt = 0;
    i64 sum = 0;
    for (i64 &i : v) {
        cin >> i;
        s.insert(i);
        sum += i;
        cnt += (sum % 2 == 0) && s.count(sum / 2);
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}
