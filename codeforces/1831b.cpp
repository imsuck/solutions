#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

void solve() {
    int n, mx = 0, hi = 0;
    cin >> n;
    int a[n + 1], b[n + 1];
    int ma[2 * n + 1], mb[2 * n + 1];
    fill_n(ma, 2 * n + 1, 0);
    fill_n(mb, 2 * n + 1, 0);
    int curr = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i - 1 >= 1 && a[i - 1] == a[i])
            curr++;
        else
            curr = 1;
        ma[a[i]] = max(ma[a[i]], curr);
        hi = max(hi, a[i]);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (i - 1 >= 1 && b[i - 1] == b[i])
            curr++;
        else
            curr = 1;
        mb[b[i]] = max(mb[b[i]], curr);
        hi = max(hi, b[i]);
    }
    for (int i = 1; i <= hi; i++)
        mx = max(mx, ma[i] + mb[i]);
    cout << mx << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--)
        solve();

    return 0;
}
