#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef string str;
#define vec vector

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, mx = 0;
    cin >> n;
    vec<array<ll, 3>> a(n);
    ll dp[n];
    fill_n(dp, n, 0);

    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        if (a[i][0] < a[i][1])
            swap(a[i][0], a[i][1]);
    }
    sort(a.rbegin(), a.rend());

    for (int i = 0; i < n; i++) {
        dp[i] = a[i][2];
        for (int j = 0; j < i; j++)
            if (a[j][1] >= a[i][1])
                dp[i] = max(dp[i], dp[j] + a[i][2]);
        mx = max(mx, dp[i]);
    }

    cout << mx << "\n";

    return 0;
}
