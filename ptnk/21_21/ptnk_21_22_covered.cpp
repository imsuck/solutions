#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    // Didn't know such knowledge could come in handy
    int left = min(x1, x3);
    int right = max(x2, x4);
    int bottom = min(y1, y3);
    int top = max(y2, y4);
    int w1 = x2 - x1;
    int w2 = x4 - x3;
    int h1 = y2 - y1;
    int h2 = y4 - y3;

    int horizontal_gap = max(0, right - left - w1 - w2);
    int vertical_gap = max(0, top - bottom - h1 - h2);

    int res = horizontal_gap * horizontal_gap + vertical_gap * vertical_gap;

    cout << res << "\n";

    return 0;
}
