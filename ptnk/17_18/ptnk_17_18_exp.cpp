#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, val = 0, min_add = 1e10, max_sub = -1e10;
    cin >> n;

    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (i % 2 == 0) {
            val += a;
            min_add = min(min_add, a);
        } else {
            val -= a;
            max_sub = max(max_sub, a);
        }
    }

    long long new_val = val + 2 * max_sub - 2 * min_add;
    cout << max(val, new_val) << "\n";

    return 0;
}
