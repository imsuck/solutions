#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(2);

    long long a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    if (b * d - e * a == 0) {
        if (b * f - e * c == 0 || e * d - a * f == 0) {
            cout << "VOSONGHIEM";
        } else {
            cout << "VONGHIEM";
        }
        return 0;
    }

    double x = (double)(b * f - e * c) / (b * d - e * a);
    double y = (double)(a * f - c * d) / (a * e - b * d);

    if (abs(x) < 0.005) {
        x = 0;
    }
    if (abs(y) < 0.005) {
        y = 0;
    }

    cout << x << " " << y;

    return 0;
}
