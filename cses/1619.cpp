#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i32 = int32_t;

void solve() {
    i32 n;
    cin >> n;
    vector<pair<i32, i32>> v(n*2);
    for (i32 i = 0; i < n; i++) {
        cin >> v[2*i].first >> v[2*i+1].first;
        v[2*i].second = 1, v[2*i+1].second = -1;
    }
    sort(v.begin(), v.end());
    i32 cnt = 0, mx = 0;
    for (auto &p : v) {
        cnt += p.second;
        mx = max(mx, cnt);
    }
    cout << mx << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
