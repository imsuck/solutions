#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n, res;
    cin >> n;
    int a[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    res = abs(a[1] - a[n]);
    for (int i = 2; i <= n / 2; i++)
        res = __gcd(res, abs(a[i] - a[n - i + 1]));
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
