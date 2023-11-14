// Unsolved
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> a(n, vector<int>(n)), rev_a(n, vector<int>(n)),
            stuff(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                bool inp;
                cin >> inp;
                a[i][j] = !inp;
                rev_a[n - 1 - i][n - 1 - j] = !inp;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                stuff[i][j] = a[i][j] || rev_a[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] != stuff[i][j]) {
                    k--;
                }
            }
        }
        if (k < 0 || k % 2 != 0) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
