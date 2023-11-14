#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using str = string;
#define vec vector

const i32 N = 1001;
i32 n, m;
bool vis[N][N];
char g[N][N], dir[N][N];

void bfs(pair<i32, i32> start) {
    queue<tuple<i32, i32, char>> q;
    q.push({start.first, start.second, '!'});
    while (!q.empty()) {
        auto [x, y, direction] = q.front();
        q.pop();
        if (y < 0 || y >= n || x < 0 || x >= m || vis[y][x] || g[y][x] == '#') {
            continue;
        }
        vis[y][x] = true;
        dir[y][x] = direction;
        q.push({x, y - 1, 'U'});
        q.push({x, y + 1, 'D'});
        q.push({x - 1, y, 'L'});
        q.push({x + 1, y, 'R'});
    }
}

void solve() {
    cin >> n >> m;
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    i32 x, y;
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            if (g[i][j] == 'A') {
                bfs({j, i});
            } else if (g[i][j] == 'B') {
                x = j, y = i;
            }
        }
    }
    if (!vis[y][x]) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        str ans = "";
        while (dir[y][x] != '!') {
            ans += dir[y][x];
            if (dir[y][x] == 'L') {
                x++;
            } else if (dir[y][x] == 'R') {
                x--;
            } else if (dir[y][x] == 'U') {
                y++;
            } else if (dir[y][x] == 'D') {
                y--;
            }
        }
        reverse(ans.begin(), ans.end());
        cout << ans.size() << "\n" << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
