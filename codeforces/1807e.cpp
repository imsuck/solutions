#include <bits/stdc++.h>
using namespace std;

/// Sum from prefix [l, r]
int sum_pre(int l, int r, int sums[]) {
    if (l == 0)
        return sums[r];
    return sums[r] - sums[l - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        int a[n + 1], sums[n + 1];
        sums[0] = 0;

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sums[i] = sums[i - 1] + a[i];
        }

        int l = 1, r = n, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            cout << "? " << (mid - l + 1);
            for (int i = l; i <= mid; i++)
                cout << " " << i;
            cout << "\n" << flush;
            int x;
            cin >> x;
            if (sum_pre(l, mid, sums) == x) {
                l = mid + 1;
            } else {
                r = mid - 1;
                ans = mid;
            }
        }
        cout << "! " << ans << "\n" << flush;
    }

    return 0;
}
