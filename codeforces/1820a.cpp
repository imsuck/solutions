#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;

    while (tt--) {
        string s;
        cin >> s;
        int n = s.size(), cnt = 0, len = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '_') {
                len++;
            } else {
                cnt += max(len - 1, 0);
                len = 0;
            }
        }
        cnt += max(len - 1, 0);

        if (s == "^")
            cout << "1";
        else
            cout << cnt + (s[0] == '_' ? 1 : 0) + (s[n - 1] == '_' ? 1 : 0);
        cout << "\n";
    }

    return 0;
}
