#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--) {
        ll n, res = 1;
        cin >> n;
        ll a[n + 1], b[n + 1], less[n + 1];
        fill_n(less, n + 1, 0);
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        sort(a + 1, a + n + 1);
        sort(b + 1, b + n + 1);
        int j = 1;
        for (int i = 1; i <= n; i++) {
            less[i] = less[i - 1];
            while (j < n && b[j] < a[i]) {
                j++;
                less[i]++;
            }
            if (b[j] < a[i])
                less[i]++;
            less[i] = min(less[i], n);
        }
        for (int i = 1; i <= n; i++)
            res = (res * (less[i] - i + 1)) % MOD;

        cout << res << "\n";
    }

    return 0;
}
