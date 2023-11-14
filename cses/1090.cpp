#include "bits/stdc++.h"
using namespace std;

int main() {
    int n, x, c, l = 0, r;
    cin >> n >> x, r = (c = n) - 1;
    vector<int> p(n);
    for (int &_ : p) {
        cin >> _;
    }
    sort(p.begin(), p.end());
    while (l < r) {
        while (p[l] + p[r] > x) {
            r--;
        }
        c -= l++ < r--;
    }
    cout << c << "\n";
}
