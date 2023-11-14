#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    long x, y;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> y >> x;
        long a = max(x, y);
        long long val;
        if (a % 2 == 0) {
            val = a * a - x + y - a + 1;
        } else {
            val = a * a + x - y - a + 1;
        }
        cout << val << "\n";
    }
}
