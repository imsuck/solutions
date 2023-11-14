#include <bits/stdc++.h>
using namespace std;

bool in_corner(int x, int y, int n, int m) {
    return x == 1 && y == 1 || x == 1 && y == m || x == n && y == 1 ||
           x == n && y == m;
}

bool on_edge(int x, int y, int n, int m) {
    return (x == 1 ^ y == 1) ^ (x == n ^ y == m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (in_corner(x1, y1, n, m) || in_corner(x2, y2, n, m)) {
            cout << "2\n";
            continue;
        } else if (on_edge(x1, y1, n, m) || on_edge(x2, y2, n, m)) {
            cout << "3\n";
            continue;
        }
        cout << "4\n";
    }

    return 0;
}
