#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    map<ll, ll> m;
    ll cnt = 0, a, s = 0;
    m[0] = 1;

    for (int i = 1; i <= n; i++) {
        cin >> a;
        s += a;
        cnt += m[s - x];
        m[s]++;
    }

    cout << cnt << "\n";

    return 0;
}
