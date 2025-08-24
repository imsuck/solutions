#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto
i32 dx[]{-1, 0, 1, 0}, dy[]{0, -1, 0, 1};
char dir[]{'U', 'L', 'D', 'R'};
const i32 inf = 1 << 30;

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<str> b(n);

    using P = pair<i32, i32>;
    queue<P> q;
    vec<vec<i32>> d(n, vec<i32>(m, inf));
    vec<vec<i32>> dp(n, vec<i32>(m, -1));
    vec<vec<char>> tr(n, vec<char>(m, '!'));
    i32 px, py = 0;
    for (i32 i = 0; i < n; i++) {
        cin >> b[i];
        for (i32 j = 0; j < m; j++) {
            if (b[i][j] == 'M') d[i][j] = 0, q.emplace(i, j);
            if (b[i][j] == 'A') {
                tie(px, py) = tie(i, j), dp[i][j] = 0;
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    cout << "YES\n0\n";
                    return;
                }
            }
        }
    }
    auto bad = [&](i32 x, i32 y) {
        if (x < 0 || n <= x) return true;
        if (y < 0 || m <= y) return true;
        return b[x][y] == '#';
    };
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        for (i32 i = 0; i < 4; i++) {
            i32 nx = x + dx[i], ny = y + dy[i];
            if (bad(nx, ny) || d[nx][ny] != inf) continue;
            d[nx][ny] = d[x][y] + 1;
            q.emplace(nx, ny);
        }
    }
    q.emplace(px, py);
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        for (i32 i = 0; i < 4; i++) {
            i32 nx = x + dx[i], ny = y + dy[i];
            if (bad(nx, ny) || b[nx][ny] == '#' || tr[nx][ny] != '!' ||
                dp[nx][ny] != -1)
                continue;
            dp[nx][ny] = dp[x][y] + 1;
            if (d[nx][ny] <= dp[nx][ny]) continue;
            tr[nx][ny] = dir[i];
            q.emplace(nx, ny);
        }
    }
    for (i32 i = 0; i < n; i++) {
        if (tr[i][0] != '!') {
            tie(px, py) = pair(i, 0);
            break;
        }
        if (tr[i][m - 1] != '!') {
            tie(px, py) = pair(i, m - 1);
            break;
        }
    }
    for (i32 i = 0; i < m; i++) {
        if (tr[0][i] != '!') {
            tie(px, py) = pair(0, i);
            break;
        }
        if (tr[n - 1][i] != '!') {
            tie(px, py) = pair(n - 1, i);
            break;
        }
    }
    str path;
    for (; tr[px][py] != '!';) {
        char c = tr[px][py];
        path += c;
        if (c == 'L') {
            py++;
        } else if (c == 'U') {
            px++;
        } else if (c == 'R') {
            py--;
        } else if (c == 'D') {
            px--;
        }
    }
    if (path.size() == 0) {
        cout << "NO\n";
        return;
    }
    reverse(begin(path), end(path));
    cout << "YES\n" << path.size() << "\n" << path << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
