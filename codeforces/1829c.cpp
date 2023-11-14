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
        map<string, int> m;
        m["00"] = m["01"] = m["10"] = m["11"] = 1e9;
        for (int i = 0; i < n; i++) {
            int t;
            cin >> t;
            string s;
            cin >> s;
            m[s] = min(m[s], t);
        }
        int res = min(m["11"], m["10"] + m["01"]);
        cout << ((res != 1e9) ? res : -1) << "\n";
    }

    return 0;
}
