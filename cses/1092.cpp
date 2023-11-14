#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long n;
    cin >> n;
    long x = n * (n + 1);
    if (x % 4 != 0) {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";
    long e = -1, c = 0, s = 0, p;

    for (int i = 1; i <= n; i++) {
        c++;
        s += i;
        if (s > x / 4) {
            e = s - x / 4;
            p = i;
            c--;
            break;
        } else if (s == x / 4) {
            e = 0;
            p = i;
        }
    }
    cout << c << "\n";
    for (int i = 1; i <= p; i++) {
        if (i != e) {
            cout << i << " ";
        }
    }
    cout << "\n";
    cout << n - c << "\n";
    if (e > 0)
        cout << e << " ";
    for (int i = p + 1; i <= n; i++) {
        cout << i << " ";
    }

    return 0;
}
