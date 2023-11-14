#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;

void solve() {
    i32 n;
    cin >> n;
    vector<i32> v(n);
    for (i32 &i : v) {
        cin >> i;
    }
    map<i32, i32> m;
    i32 l = 0, r = 0, mx = 1;
    while (r < n) {
        m[v[r]]++;
        while (m[v[r]] > 1) {
            m[v[l++]]--;
        }
        mx = max(mx, (r++) - l + 1);
    }
    cout << mx << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
