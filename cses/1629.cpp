#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;

void solve() {
    i32 n;
    cin >> n;
    vector<pair<i32, i32>> v(n);
    for (auto &p : v) {
        cin >> p.second >> p.first;
    }
    sort(v.begin(), v.end());
    i32 prev = -1, cnt = 0;
    for (const auto &p : v) {
        if (p.second >= prev) {
            cnt++, prev = p.first;
        }
    }
    cout << cnt << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
