#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n; i += 1) {
        ll x;
        cin >> x;
        double delta = round(cbrt(x)) - cbrt(x);
        if (delta < 0 && delta > -1e-9 || delta > 0 && delta < 1e-9 ||
            delta == 0) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        cout << "\n";
    }
}
