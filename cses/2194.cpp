#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;

using Pt = pair<i64, i64>;
#define x first
#define y second

void solve() {
    i32 n;
    cin >> n;
    vector<Pt> v(n);
    for (Pt &p : v) {
        cin >> p.x >> p.y;
    }
    sort(v.begin(), v.end());
    i64 dd = INT64_MAX;
    set<Pt> s;
    for (i32 l = 0, r = 0; r < n; r++) {
        i64 d = ceil(sqrtl(dd));
        while (v[r].x - v[l].x >= d) {
            s.erase({v[l].y, v[l].x});
            l++;
        }
        auto low = s.lower_bound({v[r].y - d, v[r].x});
        auto up = s.upper_bound({v[r].y + d, v[r].x});
        for (auto it = low; it != up; it++) {
            i64 dx = v[r].x - it->y;
            i64 dy = v[r].y - it->x;
            dd = min(dd, dx * dx + dy * dy);
        }
        s.insert({v[r].y, v[r].x});
    }
    cout << dd << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
