#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<uint> v(n);
    unordered_map<uint, uint> m;

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        m[v[i]]++;
    }

    cout << m.size() << "\n";

    for (int i = 0; i < n; i++) {
        if (m[v[i]] != 0) {
            cout << v[i] << " " << m[v[i]] << "\n";
            m.erase(v[i]);
        }
    }

    return 0;
}
