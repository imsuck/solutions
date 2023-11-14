#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define vec vector

ll a[1005][1005];
ll n, m;
ll vol = 0, mx = 0;

void dfs(int x, int y, vec<vec<bool>> &v) {
    if (v[x][y] || a[x][y] == 0)
        return;

    vol += a[x][y];

    v[x][y] = true;
    if (x + 1 < n)
        dfs(x + 1, y, v);
    if (y + 1 < m)
        dfs(x, y + 1, v);
    if (x > 0)
        dfs(x - 1, y, v);
    if (y > 0)
        dfs(x, y - 1, v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        mx = 0;

        cin >> n >> m;
        vec<vec<bool>> visited(n, vec<bool>(m, false));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> a[i][j];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && a[i][j] != 0) {
                    vol = 0;
                    dfs(i, j, visited);
                    mx = max(mx, vol);
                }
            }
        }
        cout << mx << "\n";
    }

    return 0;
}
