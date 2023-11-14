#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> vis, ans;

bool dfs(int v) {
    if (vis[v] == 1) {
        return false;
    }
    if (vis[v] == 2) {
        return true;
    }
    vis[v] = 1;
    for (int u : g[v]) {
        if (!dfs(u)) {
            return false;
        }
    }
    vis[v] = 2;
    ans.push_back(v);
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    g.resize(n + 1);
    vis.assign(n + 1, false);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfs(i)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    reverse(ans.begin(), ans.end());
    for (int v : ans) {
        cout << v << " ";
    }
    cout << "\n";
}
