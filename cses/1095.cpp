#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        ll a, b, res = 1;
        cin >> a >> b;
        while (b > 0) {
            res = (b & 1) ? res * a % MOD : res;
            b >>= 1;
            a = a * a % MOD;
        }
        cout << res << "\n";
    }
}
