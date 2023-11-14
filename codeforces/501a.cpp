#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int m = max(3 * a / 10, a - a / 250 * c);
    int v = max(3 * b / 10, b - b / 250 * d);

    if (m > v) {
        cout << "Misha\n";
    } else if (v > m) {
        cout << "Vasya\n";
    } else {
        cout << "Tie\n";
    }

    return 0;
}
