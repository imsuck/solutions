#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--) {
        int n, t, idx = -1, mx = 0;
        cin >> n >> t;
        int a[n + 1], b;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++, t--) {
            cin >> b;
            if (b > mx && a[i] <= t) {
                mx = b;
                idx = i;
            }
        }
        cout << idx << "\n";
    }

    return 0;
}
