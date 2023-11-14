#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, h, t;
    cin >> n >> m;
    multiset<int> s;
    while (n--) {
        cin >> h;
        s.insert(h);
    }
    while (m--) {
        cin >> t;
        auto i = s.upper_bound(t);
        if (i == s.begin()) {
            cout << "-1\n";
        } else {
            i--;
            cout << *i << "\n";
            s.erase(i);
        }
    }
}
