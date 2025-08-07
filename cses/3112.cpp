#include <bits/stdc++.h>
using namespace std;

bool ask(int y) {
    cout << "? " << y << endl;
    string s;
    cin >> s;
    return s[0] == 'Y';
}

void solve() {
    int l = 0, r = (int)1e9 + 1, m;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (ask(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << "! " << r << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
