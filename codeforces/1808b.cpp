#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        i64 n, m;
        i64 chips = 0;
        cin >> n >> m;
        int v[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> v[i][j];
        for (int j = 0; j < m; j++) {
            vector<int> a;
            for (int i = 0; i < n; i++)
                a.push_back(v[i][j]);
            sort(a.begin(), a.end());
            for (i64 i = 0; i < n; i++)
                chips += (2LL * i - n + 1) * a[i];
        }
        cout << chips << "\n";
    }

    return 0;
}
