#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, ans = 0;
    cin >> n;
    int a[n + 1];
    int pref[n + 1];
    pref[0] = 0;

    for (int i = 1; i < n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n && pref[j] - pref[i] <= pref[i]; j++)
            if (pref[j] - pref[i] == pref[i])
                ans = max(ans, j - i);

    cout << ans << "\n";

    return 0;
}
