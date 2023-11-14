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
        ll n, res = 1e9;
        cin >> n;
        ll p[n + 1];
        vec<ll> g;

        for (int i = 1; i <= n; i++)
            cin >> p[i];
        for (int i = 1; i <= n; i++) {
            while (p[i] != i) {
                g.push_back(abs(i - p[i]));
                swap(p[i], p[p[i]]);
            }
        }
        res = g[0];
        for (int i = 1; i < g.size(); i++)
            res = __gcd(res, g[i]);

        cout << res << "\n";
    }

    return 0;
}
