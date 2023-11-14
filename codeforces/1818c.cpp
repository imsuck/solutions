#include <bits/stdc++.h>
using namespace std;

void sol() {
    int n, q;
    cin >> n >> q;
    int a[n + 5], pref[n + 5];
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] +
                  (i >= 2 && a[i - 2] >= a[i - 1] && a[i - 1] >= a[i] ? 1 : 0);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;

        if (len <= 2) {
            cout << len << "\n";
            continue;
        }

        int new_len = len - pref[r] + pref[l + 1];

        cout << new_len << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sol();

    return 0;
}
