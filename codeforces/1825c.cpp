#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#define dbg(a) cout << a << "\n";

typedef long long ll;
typedef unsigned long long ull;
#define vec vector

void solve() {
    ll n, m, ty1 = 0, ty2 = 0, res = 0;
    cin >> n >> m;
    vec<ll> occ_i;

    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        if (a == -1)
            ty1++;
        else if (a == -2)
            ty2++;
        else
            occ_i.push_back(a);
    }
    sort(occ_i.begin(), occ_i.end());
    occ_i.erase(unique(occ_i.begin(), occ_i.end()), occ_i.end());
    for (int i = 0, _n = occ_i.size(); i < _n; i++)
        res = max(res, min(occ_i[i] - 1, ty1 + i) +
                           min(m - occ_i[i] + 1, ty2 + _n - i));

    res = max({res, ty1 + (ll)occ_i.size(), ty2 + (ll)occ_i.size()});
    res = min(res, m);
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
