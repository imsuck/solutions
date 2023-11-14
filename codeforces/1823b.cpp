#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, k, off = 0;
        cin >> n >> k;
        int p[n + 1];
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if ((p[i] - i % k) % k != 0)
                off++;
        }
        if (off == 0)
            cout << "0\n";
        else if (off == 2)
            cout << "1\n";
        else if (off > 2)
            cout << "-1\n";
    }

    return 0;
}
