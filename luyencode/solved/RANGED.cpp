#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a <= d && c <= b) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
