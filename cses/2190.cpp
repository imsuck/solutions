#include <bits/stdc++.h>
using namespace std;

using i = int64_t;

struct P {
    i x, y;
};

i o(P a, P b, P c) {
    i v = a.x * (c.y - b.y) + b.x * (a.y - c.y) + c.x * (b.y - a.y);
    if (v == 0)
        return 0;
    return v > 0 ? 1 : -1;
}

bool p(P a, P b, P c) {
    return (c.x - a.x) * (c.x - b.x) <= 0 && (c.y - a.y) * (c.y - b.y) <= 0;
}

bool h(P a, P b, P c, P d) {
    if (o(a, b, c) * o(a, b, d) > 0 || o(c, d, a) * o(c, d, b) > 0)
        return false;
    if (o(a, b, c) == 0 && !p(a, b, c) && o(a, b, d) == 0 && !p(a, b, d) &&
        o(c, d, a) == 0 && !p(c, d, a) && o(c, d, b) == 0 && !p(c, d, b))
        return false;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i t;
    cin >> t;
    while (t--) {
        P p1, p2, p3, p4;
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;
        cout << (h(p1, p2, p3, p4) ? "YES\n" : "NO\n");
    }
}
