#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, res = 0;
    cin >> n >> m;
    int a[n];

    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);

    for (int i = 0; i < n; i++) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            if (i == l) {
                l++;
            } else if (i == r) {
                r--;
            } else if (a[i] + a[l] + a[r] < m) {
                res = max(res, a[i] + a[l] + a[r]);
                l++;
            } else if (a[i] + a[l] + a[r] > m) {
                r--;
            } else {
                cout << m << "\n";
                return 0;
            }
        }
    }

    cout << res << "\n";

    return 0;
}
