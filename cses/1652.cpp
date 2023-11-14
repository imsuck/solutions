#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q, p[1001][1001], a, b, c;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char h;
            cin >> h;
            p[i][j] = (h == '*') + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
        }
    }
    while (q--) {
        cin >> a >> b >> c >> n;
        cout << p[c][n] - p[--a][n] - p[c][--b] + p[a][b] << "\n";
    }
}
