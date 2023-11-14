#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define vec vector

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, k, mx = 0;
    cin >> n >> k;
    ll w = 0;
    while (1 << (w + 1) <= k)
        w++;
    vec<vec<ll>> st(n + 1, vec<ll>(w + 1, -1));

    for (int i = 1; i <= n; i++)
        cin >> st[i][0];

    for (int j = 1; j <= w; j++)
        for (int i = 1; i + (1 << (j - 1)) <= n; i++)
            st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);

    for (int i = 1; i + k - (1 << w) <= n; i++)
        mx = max(mx, __gcd(st[i][w], st[i + k - (1 << w)][w]));

    cout << mx << "\n";

    return 0;
}
