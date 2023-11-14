#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, m;
    cin >> n >> m;
    long long a[n], b[m], pref_sum[m];

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    sort(b, b + m);
    for (int i = 0; i < m; i++)
        if (i == 0)
            pref_sum[i] = b[i];
        else
            pref_sum[i] = pref_sum[i - 1] + b[i];

    for (int i = 0; i < n; i++) {
        int idx = upper_bound(b, b + m, a[i]) - b - 1;
        int prev_idx = -1;
        if (a[i] < b[0])
            continue;

        a[i] += pref_sum[idx];

        while (1) {
            int j = upper_bound(b, b + m, a[i]) - b - 1;
            if (j == idx)
                break;
            a[i] += pref_sum[j] - pref_sum[idx];
            idx = j;
        }
    }

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";

    return 0;
}
