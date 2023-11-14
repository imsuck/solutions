#include <bits/stdc++.h>
using namespace std;

#define lol long long

lol diff(lol x, lol y) { return max(x, y) - min(x, y); }

lol max_4(lol x, lol y, lol z, lol w) { return max(max(x, y), max(z, w)); }
lol min_4(lol x, lol y, lol z, lol w) { return min(min(x, y), min(z, w)); }

int main() {
    int ax1, ay1, ax2, ay2;
    cin >> ax1 >> ay1 >> ax2 >> ay2;
    int bx1, by1, bx2, by2;
    cin >> bx1 >> by1 >> bx2 >> by2;
    lol area;

    lol diff_x =
        max(0LL, (diff(ax1, ax2) + diff(bx1, bx2) - max_4(ax1, ax2, bx1, bx2) +
                  min_4(ax1, ax2, bx1, bx2)));
    lol diff_y =
        max(0LL, (diff(ay1, ay2) + diff(by1, by2) - max_4(ay1, ay2, by1, by2) +
                  min_4(ay1, ay2, by1, by2)));

    area = diff_x * diff_y;

    cout << area;

    return 0;
}
