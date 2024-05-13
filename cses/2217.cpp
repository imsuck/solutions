#include <bits/stdc++.h>
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
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n, q;
    cin >> n >> q;
    vec<i32> p1(n + 2), p2(n + 2);
    p1[0] = p2[0] = 0, p1[n+1] = p2[n+1] = 1e6;
    i32 cnt = 1;
    for (i32 i = 1; i <= n; i++) {
        cin >> p1[i];
        p2[p1[i]] = i;
    }
    for (i32 i = 2; i <= n; i++) {
        cnt += p2[i] < p2[i - 1];
    }
    dbg(cnt);
    while (q--) {
        i32 a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);

        i32 l = p1[a], r = p1[b];
        swap(p1[a], p1[b]);

        if (p2[l-1] <= p2[l] && p2[l-1] > b) cnt++;
        if (p2[l-1] > p2[l] && p2[l-1] <= b) cnt--;
        if (p2[l] <= p2[l+1] && b > p2[l+1]) cnt++;
        if (p2[l] > p2[l+1] && b <= p2[l+1]) cnt--;
        p2[l] = b;
        if (p2[r-1] <= p2[r] && p2[r-1] > a) cnt++;
        if (p2[r-1] > p2[r] && p2[r-1] <= a) cnt--;
        if (p2[r] <= p2[r+1] && a > p2[r+1]) cnt++;
        if (p2[r] > p2[r+1] && a <= p2[r+1]) cnt--;
        p2[r] = a;

        cout << cnt << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}
