#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;
        ll a[n + 1], s[n + 1], mx = 0;
        s[0] = 0;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + a[i];

        for (int x = 0; x <= k; x++) {
            int y = k - x;
            mx = max(mx, s[n - y] - s[2 * x]);
        }

        cout << mx << "\n";
    }

    return 0;
}
