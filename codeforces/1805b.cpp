#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        char small = 'z';
        int idx = 0;

        for (int i = 0; i < n; i++) {
            if (small >= s[i]) {
                small = s[i];
                idx = i;
            }
        }

        string res = string(1, small);
        for (int i = 0; i < n; i++) {
            if (i != idx)
                res += s[i];
        }

        cout << res << "\n";
    }

    return 0;
}
