#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (0)
#endif

void solve() {
    int n;
    cin >> n;
    cout << n;
    while (n > 1) {
        n = n & 1 ? 3 * n + 1 : n / 2;
        cout << " " << n;
    }
    cout << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
