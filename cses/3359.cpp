#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (0)
#endif

using i64 = int64_t;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector g(n, vector(n, 'A')), vis(n, vector<char>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }

    string ans;
    char best = char(127), prv = 0;
    queue<tuple<int, int, char>> q;
    q.emplace(0, 0, 0);
    while (q.size()) {
        auto [x, y, p] = q.front();
        q.pop();
        if (x + y > ans.size()) ans += (prv = exchange(best, 127));
        if (p != prv || vis[x][y]) continue;
        vis[x][y] = true;
        best = min(best, g[x][y]);
        if (x + 1 < n) q.emplace(x + 1, y, g[x][y]);
        if (y + 1 < n) q.emplace(x, y + 1, g[x][y]);
    }
    cout << ans + g.back().back() << "\n";
}
