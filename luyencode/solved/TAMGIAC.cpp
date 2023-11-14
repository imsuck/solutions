#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(2);

    int a, b, c;
    cin >> a >> b >> c;

    if (a + b <= c || b + c <= a || c + a <= b) {
        cout << "NO";
        return 0;
    }

    cout << a + b + c << " ";
    double s = (double)(a + b + c) / 2;
    cout << sqrt(s * (s - a) * (s - b) * (s - c));

    return 0;
}
