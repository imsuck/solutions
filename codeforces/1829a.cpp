#include <bits/stdc++.h>
using namespace std;

const string nice_s = "codeforces";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int cnt = 0;
        string s;
        cin >> s;

        for (int i = 0; i < s.size(); i++)
            if (s[i] != nice_s[i])
                cnt++;
        cout << cnt << "\n";
    }

    return 0;
}
