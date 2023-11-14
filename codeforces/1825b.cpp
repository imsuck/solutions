#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define vec vector

const int INF = 1e6;

void solve() {
    int n, m;
    cin >> n >> m;
    int mn1 = INF, mn2 = INF, mx1 = -INF, mx2 = -INF;

    if (n < m)
        swap(n, m);

    for (int i = 0; i < n * m; i++) {
        int a;
        cin >> a;
        if (a < mn1) {
            mn2 = mn1;
            mn1 = a;
        } else if (a < mn2)
            mn2 = a;
        if (a > mx1) {
            mx2 = mx1;
            mx1 = a;
        } else if (a > mx2)
            mx2 = a;
    }
    int res = m * (n - 1) * (mx1 - mn1) +
              max((m - 1) * (mx1 - mn2), (m - 1) * (mx2 - mn1));
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}
