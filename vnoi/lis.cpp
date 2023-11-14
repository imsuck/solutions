#include <bits/stdc++.h>
using namespace std;

const long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, ans = 1;
    cin >> n;
    long a[n];
    vector<long> min_len(n + 1, INF);
    min_len[0] = -INF;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int idx =
            lower_bound(min_len.begin(), min_len.end(), a[i]) - min_len.begin();
        min_len[idx] = a[i];
        ans = max(ans, idx);
    }
    cout << ans << "\n";

    return 0;
}
