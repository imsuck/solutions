#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    long a, b;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> a >> b;
        while (a > 0 && b > 0) {
            if (a > b) {
                long diff = (a - b + 1) / 2;
                a -= diff * 2;
                b -= diff;
            } else if (a == b) {
                if (a % 3 != 0) {
                    a = -1;
                    b = -1;
                    continue;
                } else {
                    a = 0;
                    b = 0;
                    continue;
                }
            } else {
                long diff = (b - a + 1) / 2;
                a -= diff;
                b -= diff * 2;
            }
        }

        if (a == 0 && b == 0)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
