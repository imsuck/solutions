#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;
#define vec vector

struct Pt {
    i64 x, y;
};

istream &operator>>(istream &is, Pt &point) { return is >> point.x >> point.y; }

void solve() {
    i32 n;
    cin >> n;
    vec<Pt> v(n);
    for (Pt &p : v) {
        cin >> p;
    }
    i64 area = 0, boundaries = 0;
    for (i32 i = 0; i < n; i++) {
        i32 j = (i + 1) % n;
        area += v[i].x * v[j].y - v[j].x * v[i].y;
    }
    for (i32 i = 0; i < n; i++) {
        i32 j = (i + 1) % n;
        boundaries += __gcd(abs(v[i].x - v[j].x), abs(v[i].y - v[j].y));
    }
    cout << (abs(area) - boundaries) / 2 + 1 << " " << boundaries << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
