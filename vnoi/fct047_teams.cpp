#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long a, b, c;
    cin >> a >> b >> c;

    long pairs = min(a / 2, b);
    long rem = a + b - 3 * pairs;

    cout << pairs - int(ceil(double(max(0l, c - rem)) / 3)) << "\n";

    return 0;
}
