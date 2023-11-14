#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m, x = -1, y = -1;
        cin >> n >> m;
        map<int, int> f;
        vec<int> g[n + 1];
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 1; i <= n; i++)
            f[g[i].size()]++;

        for (auto it = f.begin(); it != f.end(); it++) {
            if (it->first <= 1)
                continue;
            if (it->second == 1) {
                x = it->first;
            } else {
                y = it->first - 1;
            }
        }
        if (x == -1) {
            x = y + 1;
        }
        cout << x << " " << y << "\n";
    }

    return 0;
}
