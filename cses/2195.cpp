#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

struct Pt {
    i64 x, y;
};

i64 oa(Pt a, Pt b, Pt c) {
    i64 v = -(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    return v < 0 ? -1 : v > 0 ? 1 : 0;
}

void solve() {
    i64 n;
    cin >> n;
    vector<Pt> v(n);
    for (Pt &p : v) {
        cin >> p.x >> p.y;
    }
    sort(v.begin(), v.end(),
         [](Pt a, Pt b) { return a.x < b.x || a.x == b.x && a.y < b.y; });
    vector<Pt> up{v[0]}, down{v[0]};
    for (i64 i = 1; i < n; i++) {
        while (up.size() > 1 &&
               oa(up[up.size() - 2], up[up.size() - 1], v[i]) < 0) {
            up.pop_back();
        }
        up.push_back(v[i]);
        while (down.size() > 1 &&
               oa(down[down.size() - 2], down[down.size() - 1], v[i]) > 0) {
            down.pop_back();
        }
        down.push_back(v[i]);
    }
    cout << up.size() + down.size() - 2 << "\n";
    for (Pt p : up) {
        cout << p.x << " " << p.y << "\n";
    }
    for (i64 i = 1; i < down.size() - 1; i++) {
        cout << down[i].x << " " << down[i].y << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
