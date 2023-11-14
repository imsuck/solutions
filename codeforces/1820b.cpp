#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        s += s;
        long long len = 0, mx_len = 0;
        for (int i = 0; i < 2 * n; i++) {
            len = (s[i] == '1') ? len + 1 : 0;
            mx_len = max(mx_len, len + 1);
        }
        if (mx_len >= n + 1)
            cout << (long long)n * n;
        else if (mx_len % 2 == 0)
            cout << mx_len * mx_len / 4;
        else
            cout << (mx_len / 2) * (mx_len / 2 + 1);
        cout << "\n";
    }

    return 0;
}
