#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
#define vec vector

i32 n, m;
vec<char> rooms;
vec<bool> vis;

i32 idx(i32 x, i32 y) { return x + y * n; }

void dfs(i32 x, i32 y) {
    if (x < 0 || x >= n || y < 0 || y >= m || vis[idx(x, y)]) {
        return;
    }
    vis[idx(x, y)] = true;
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}

void solve() {
    cin >> n >> m;
    rooms.resize(n * m);
    vis.resize(n * m);
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            i32 pos = idx(i, j);
            cin >> rooms[pos];
            if (rooms[pos] == '#') {
                vis[pos] = true;
            }
        }
    }
    i32 cnt = 0;
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            i32 pos = idx(i, j);
            if (!vis[pos] && rooms[pos] == '.') {
                dfs(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
