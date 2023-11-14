#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int spf(int n) {
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0)
            return i;
    return n;
}

void solve() {
    int n, m;
    cin >> n >> m;
    if (n == 1)
        cout << "YES\n";
    else if (n % 2 == 0 && m >= 2)
        cout << "NO\n";
    else if (n % 2 != 0 && (n <= m || spf(n) <= m))
        cout << "NO\n";
    else
        cout << "YES\n";
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
