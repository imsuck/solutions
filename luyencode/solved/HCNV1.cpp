#include <bits/stdc++.h>
using namespace std;

void swap(int &x, int &y) {
    x = x + y;
    y = x - y;
    x = x - y;
}

int main() {
    long long x1, y1, x2, y2, x, y;
    cin >> x1 >> y1 >> x2 >> y2 >> x >> y;

    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }

    if (x1 < x && x < x2 && y1 < y && y < y2) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
