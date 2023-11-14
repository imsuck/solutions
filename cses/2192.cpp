#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;
#define vec vector

struct Pt {
    i64 x, y;
};

istream &operator>>(istream &is, Pt &point) { return is >> point.x >> point.y; }

i32 o(Pt &a, Pt &b, Pt &c) {
    i64 s = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return s < 0 ? -1 : s > 0 ? 1 : 0;
}

bool on_seg(Pt &a, Pt &p, Pt &q) {
    return o(a, p, q) == 0 && (a.x - p.x) * (a.x - q.x) <= 0 &&
           (a.y - p.y) * (a.y - q.y) <= 0;
}

bool crosses_ray(Pt &a, Pt &p, Pt &q) {
    Pt mn = p.y < q.y ? p : q, mx = p.y >= q.y ? p : q;
    return mn.y <= a.y && a.y < mx.y && o(a, mn, mx) == 1;
}

void solve() {
    i32 n, m;
    cin >> n >> m;
    vec<Pt> polygon(n);
    for (auto &point : polygon) {
        cin >> point;
    }
    while (m--) {
        Pt cur;
        cin >> cur;
        i32 crossings = 0;
        bool f = false;
        for (i32 i = 0; i < n; i++) {
            i32 j = (i + 1) % n;
            if (on_seg(cur, polygon[i], polygon[j])) {
                f = true;
                break;
            }
            crossings += crosses_ray(cur, polygon[i], polygon[j]);
        }
        cout << (f ? "BOUNDARY" : crossings & 1 ? "INSIDE" : "OUTSIDE") << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
