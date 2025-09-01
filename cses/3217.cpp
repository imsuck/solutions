#include <bits/stdc++.h>
using namespace std;
#include "library/other/types.hpp"

i32 dx[]{-1, +1, +2, +2, +1, -1, -2, -2};
i32 dy[]{-2, -2, -1, +1, +2, +2, +1, -1};

void solve() {
    i32 n;
    cin >> n;
    vec<vec<i32>> d(n, vec<i32>(n, -1));
    queue<pair<i32, i32>> q;
    d[0][0] = 0, q.emplace(0, 0);
    auto good = [&](i32 x, i32 y) {
        if (x < 0 || n <= x) return false;
        if (y < 0 || n <= y) return false;
        return d[x][y] == -1;
    };
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        for (i32 i = 0; i < 8; i++) {
            i32 nx = x + dx[i], ny = y + dy[i];
            if (!good(nx, ny)) continue;
            d[nx][ny] = d[x][y] + 1;
            q.emplace(nx, ny);
        }
    }
    for (i32 i = 0; i < n; i++)
        for (i32 j = 0; j < n; j++) cout << d[i][j] << " \n"[j == n - 1];
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
