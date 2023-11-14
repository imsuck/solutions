#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q, a, b;
    cin >> n >> q;
    int p[n + 1]{0};
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i] ^= p[i - 1];
    }
    while (q--) {
        cin >> a >> b;
        cout << (p[b] ^ p[a - 1]) << "\n";
    }
}
