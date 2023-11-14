#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, mx = 0, len = 0;
        cin >> n;
        int a[n];

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == 0) {
                len++;
                mx = max(mx, len);
            } else {
                len = 0;
            }
        }
        cout << mx << "\n";
    }

    return 0;
}
