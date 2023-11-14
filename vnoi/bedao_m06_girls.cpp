#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long m, n, k, res = -2;
    cin >> m >> n >> k;
    long long a[m + 1], pref[m + 1];
    pref[0] = 0;

    for (int i = 1; i <= m; i++)
        cin >> a[i];
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++)
        pref[i] = pref[i - 1] + a[i];

    for (int r = m;; r--) {
        int l = r - n + 1;
        if (l <= 0)
            break;
        if (a[r] - a[l] > k)
            continue;
        res = max(res, pref[r] - pref[l - 1]);
    }

    cout << res << "\n";

    return 0;
}
