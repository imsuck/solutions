#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, w = 1;
    cin >> n;
    int a[n + 1][5];
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 0; j < 5; j++) {
            cin >> a[i][j];
            if (a[w][j] > a[i][j])
                cnt++;
            if (cnt == 3)
                w = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 0; j < 5; j++) {
            if (a[w][j] > a[i][j])
                cnt++;
            if (cnt == 3) {
                cout << "-1\n";
                return;
            }
        }
    }
    cout << w << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
