#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--) {
        str ans = "YES";
        int n, mn_o = 1e9 + 69;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mn_o = a[i] % 2 == 1 ? min(mn_o, a[i]) : mn_o;
            ans = a[i] % 2 == 1 ? "NO" : ans;
        }
        if (ans == "YES") {
            cout << ans << "\n";
            continue;
        }
        ans = "YES";
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 0 && a[i] < mn_o) {
                ans = "NO";
                break;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
