#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    long long a, sum = 0, mn = 0, mx = -1e18, mx_el = -1e18;

    while (n--) {
        cin >> a;
        sum += a;
        mx_el = max(mx_el, a);
        mn = min(mn, sum);
        mx = max(mx, sum - mn);
    }

    cout << (mx_el < 0 ? mx_el : mx) << "\n";

    return 0;
}
