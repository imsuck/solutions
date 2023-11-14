// Dead...
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;
        int coef[n];
        double magic[m];
        int arr[m];
        bool ohno[m];
        fill(ohno, ohno + m, false);

        for (int i = 0; i < n; i++) {
            cin >> coef[i];
        }
        for (int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            if (c <= 0) {
                ohno[i] = true;
                continue;
            }
            magic[i] = 2 * sqrt((long double)a * c);
            arr[i] = b;
        }

        for (int i = 0; i < m; i++) {
            if (ohno[i]) {
                cout << "NO\n";
                continue;
            } else {
                int yas = false;
                long double l = magic[i] + arr[i], r = arr[i] - magic[i];
                for (int j = 0; j < n; j++) {
                    if (l > coef[j] && coef[j] > r) {
                        cout << "YES\n" << coef[j] << "\n";
                        yas = true;
                        break;
                    }
                }
                if (!yas)
                    cout << "NO\n";
            }
        }
    }

    return 0;
}
