#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

void solve() {
    using P = array<i64, 2>;
    const i64 inf = 1.1e12;
    i32 n;
    cin >> n;
    array<P, 4> hull{
        {{inf, inf}, {inf, inf}, {-inf, -inf}, {-inf, -inf}}
    };
    auto add = [&](P p) {
        auto [x, y] = p;
        p = {x + y, x - y};
        if (hull[0][0] > p[0]) hull[0] = p;
        if (hull[1][1] > p[1]) hull[1] = p;
        if (hull[2][0] < p[0]) hull[2] = p;
        if (hull[3][1] < p[1]) hull[3] = p;
    };
    auto get = [&]() {
        i64 mx = 0;
        for (i32 i = 1; i < 4; i++) {
            for (i32 j = 0; j < i; j++) {
                mx = max(
                    {mx,
                     abs(hull[i][0] - hull[j][0]),
                     abs(hull[i][1] - hull[j][1])}
                );
            }
        }
        return mx;
    };
    while (n--) {
        i32 x, y;
        cin >> x >> y;
        add({x, y});
        cout << get() << "\n";
    }
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
