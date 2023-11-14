#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long total_value = 0;
    cin >> n >> m;
    vector<vector<int>> land(n, vector<int>(m));

    vector<vector<long long>> pref_sum(n + 1, vector<long long>(m + 1));
    // Init 2d-prefix sum array
    for (int i = 0; i <= m; i++) {
        pref_sum[0][i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        pref_sum[i][0] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> land[i][j];
            total_value += land[i][j];
            pref_sum[i + 1][j + 1] = pref_sum[i + 1][j] + pref_sum[i][j + 1] -
                                     pref_sum[i][j] + land[i][j];
        }
    }

    if (total_value % 3 != 0) {
        cout << "NO\n";
        return 0;
    }
    long long one_third = total_value / 3;

    // Sorry for the monstrosity
    for (int i = 1; i <= n && pref_sum[i][m] <= one_third; i++) {
        if (pref_sum[i][m] == one_third) {
            for (int j = i + 1;
                 j <= n && pref_sum[j][m] - pref_sum[i][m] <= one_third; j++) {
                if (pref_sum[j][m] - pref_sum[i][m] == one_third) {
                    cout << "YES\n";
                    cout << "N " << i << "\nN " << i + j << "\n";
                    return 0;
                }
            }
            for (int j = 1;
                 j <= m && pref_sum[n][j] - pref_sum[i][j] <= one_third; j++) {
                if (pref_sum[n][j] - pref_sum[i][j] == one_third) {
                    cout << "YES\n";
                    cout << "N " << i << "\nD " << j << "\n";
                    return 0;
                }
            }
        }
    }
    for (int i = 1; i <= m && pref_sum[n][i] <= one_third; i++) {
        if (pref_sum[n][i] == one_third) {
            for (int j = i + 1;
                 j <= m && pref_sum[n][j] - pref_sum[n][i] <= one_third; j++) {
                if (pref_sum[n][j] - pref_sum[n][i] == one_third) {
                    cout << "YES\n";
                    cout << "D " << j << "\nN " << j + i << "\n";
                    return 0;
                }
            }
            for (int j = 1;
                 j <= n && pref_sum[j][m] - pref_sum[j][i] <= one_third; j++) {
                if (pref_sum[j][m] - pref_sum[i][j] == one_third) {
                    cout << "YES\n";
                    cout << "D " << i << "\nN " << j << "\n";
                    return 0;
                }
            }
        }
    }

    cout << "NO\n";

    return 0;
}
