#include <iostream>

#define S std::

int main() {
    S cin.tie(0)->sync_with_stdio(false);
    long t, a, b, c, d, e, f, s;
    S cin >> t;
    while (t--)
        S cin >> a >> b >> c >> d >> e >> f,
        s = a * (d - f) + c * (f - b) + e * (b - d),
        S cout << (s > 0 ? "LEFT"
                 : s < 0 ? "RIGHT"
                         : "TOUCH") << "\n";
}
