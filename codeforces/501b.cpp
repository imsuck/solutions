#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    string o, n;
    map<string, string> m; // <og name, current name>

    for (int i = 0; i < t; i++) {
        cin >> o >> n;
        if (m[o] == "") {
            m[n] = o;
        } else {
            m[n] = m[o];
            m.erase(o);
        }
    }

    int count;
    for (auto &x : m) {
        if (!x.second.empty())
            count++;
    }
    cout << m.size() << "\n";
    for (auto &x : m) {
        if (!x.second.empty())
            cout << x.second << " " << x.first << "\n";
    }

    return 0;
}
