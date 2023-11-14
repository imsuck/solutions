#include <bits/stdc++.h>
using namespace std;

long solve(long l, long r) {}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        long l, r;
        cin >> l >> r;
        long res = solve(l, r);
        cout << "Case #" << i << ": " << res;
    }

    return 0;
}
