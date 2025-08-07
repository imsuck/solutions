#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int l = 9; l >= 0; l--) {
        string t(n, ' ');
        for (int i = 0; i < n; i++) t[i] = (i >> l & 1) + '0';
        cout << "? " + t << endl, cin >> t;
        for (int i = 0; i < n; i++) a[i] |= int(t[i] == '1') << l;
    }
    cout << "!";
    for (int i : a) cout << " " << i + 1;
    cout << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
