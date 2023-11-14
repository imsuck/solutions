#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, q;
        cin >> n >> q;
        int a[n], sums[n];
        for (int j = 0; j < n; j++) {
            cin >> a[j];
            // prefix sum
            if (j != 0)
                sums[j] = sums[j - 1] + a[j];
            else
                sums[j] = a[j];
        }
        for (int j = 0; j < q; j++) {
            int l, r, k;
            cin >> l >> r >> k;

            // 0-indexed thing;
            l--;
            r--;
            int len = r - l + 1;

            int left = 0;
            if (l > 0)
                left = sums[l - 1];
            int right = 0;
            if (r < n)
                right = sums[n - 1] - sums[r];

            // check parity & prevent overflow
            if ((k % 2 != 0 && len % 2 != 0) ^ ((left + right) % 2 != 0))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }

    return 0;
}
