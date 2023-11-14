#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int l, r;
    ll cnt = 0;
    map<int, bool> computed;
    cin >> l >> r;

    for (ll i = 2, x = 2 * i * i; i < r; i++, x = 2 * i * i) {
        for (ll j = (l * l / x) * x; j < r * r; j += i * i) {
            if (computed[j])
                continue;
            for (ll k = l; k * k < j; k++)
                if (j % k == 0 && j / k <= r)
                    cnt++;
            computed[j] = true;
        }
    }

    cout << cnt << "\n";

    return 0;
}
