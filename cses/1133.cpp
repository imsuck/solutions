#include <bits/stdc++.h>
using namespace std;
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> t(n + 1);
    for (int i = 0, u, v; i < n - 1; i++)
        cin >> u >> v, t[u].push_back(v), t[v].push_back(u);
    int d = 0;
    vector<int64_t> sz(n + 1), ans(n + 1);
    auto dfs1 = [&](auto self, int v = 1, int p = 0) -> void {
        ans[1] += d, sz[v] = 1;
        d++;
        for (int c : t[v])
            if (c != p) self(self, c, v), sz[v] += sz[c];
        d--;
    };
    dfs1(dfs1);
    auto dfs2 = [&](auto self, int v = 1, int p = 0) -> void {
        for (int c : t[v]) {
            if (c != p) {
                ans[c] = ans[v] + n - 2 * sz[c];
                self(self, c, v);
            }
        }
    };
    dfs2(dfs2);
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
}
