#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    if (n == 1) {
        cout << "01\n";
        return 0;
    }
    int m = 1 << (n - 1);
    vector<bool> vis(2 * m);
    vector<array<int, 2>> e(2 * m);
    vector<basic_string<int>> g(m);
    for (int i = 0; i < m; i++) {
        g[i] += 2 * i, e[2 * i] = {i, i >> 1};
        g[i] += 2 * i + 1, e[2 * i + 1] = {i, i >> 1 | 1 << (n - 2)};
    }
    vis.resize(e.size());
    vector<int> path, st{0};
    while (st.size()) {
        int v = st.back();
        if (g[v].empty()) {
            path.push_back(v), st.pop_back();
            continue;
        }
        int i = g[v].back();
        g[v].pop_back();
        if (vis[i]) continue;
        vis[i] = true;
        st.push_back(v ^ e[i][0] ^ e[i][1]);
    }
    string ans(n - 1, '0');
    for (int i = 1; i < path.size(); i++) ans += (path[i] & 1) + '0';
    cout << ans << "\n";
}
