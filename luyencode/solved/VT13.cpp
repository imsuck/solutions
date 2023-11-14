#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int c, max = 0, d, e;
    cin >> c;
    int a[c];

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;

        a[i] = input;
    }

    for (int i = 0; i < c; i++) {
        if (i < c - 1) {
            if (max < a[i] + a[i + 1]) {
                max = a[i] + a[i + 1];
                d = a[i];
                e = a[i + 1];
            } else if (max == a[i] + a[i + 1]) {
                d = std::max(a[i], a[i + 1]);
                e = std::min(a[i], a[i + 1]);
            }
        } else {
            if (max < a[i] + a[0]) {
                max = a[i] + a[0];
                d = a[i];
                e = a[0];
            } else if (max == a[i] + a[0]) {
                d = std::max(a[i], a[0]);
                e = std::min(a[i], a[0]);
            }
        }
    }

    cout << d << " " << e;

    return 0;
}
