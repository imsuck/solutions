#include <bits/stdc++.h>
using namespace std;
#include "library/other/types.hpp"
#include "library/other/y_combinator.hpp"

i32 dx[]{+1, +2, +2, +1, -1, -2, -2, -1};
i32 dy[]{-2, -1, +1, +2, +2, +1, -1, -2};
i32 id[8][8], vis[8][8]{};

bool ok(i32 x, i32 y) {
    return !(x < 0 || 7 < x || y < 0 || 7 < y || vis[y][x]);
}
i32 deg(i32 x, i32 y) {
    i32 d = 0;
    for (i32 i = 0; i < 8; i++) {
        i32 nx = x + dx[i], ny = y + dy[i];
        if (!ok(nx, ny)) continue;
        d++;
    }
    return d;
}

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 _x, _y;
    cin >> _x >> _y, _x--, _y--;
    y_comb([&](auto &f, i32 x, i32 y, i32 d) -> void {
        vis[y][x] = true;
        id[y][x] = d;
        if (d == 64) {
            for (i32 i = 0; i < 8; i++) {
                for (i32 j = 0; j < 8; j++) {
                    cout << id[i][j] << " \n"[j == 7];
                }
            }
            exit(0);
        }
        vec<pair<i32, i32>> nxt;
        for (i32 i = 0; i < 8; i++) {
            i32 nx = x + dx[i], ny = y + dy[i];
            if (!ok(nx, ny)) continue;
            nxt.emplace_back(nx, ny);
        }
        sort(begin(nxt), end(nxt), [](auto &a, auto &b) {
            return deg(a.first, a.second) < deg(b.first, b.second);
        });
        for (auto [nx, ny] : nxt) f(nx, ny, d + 1);
        vis[y][x] = false;
    })(_x, _y, 1);
}
