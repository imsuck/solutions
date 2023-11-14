#include <bits/stdc++.h>
using namespace std;

void move(int disk, int pos, int target) {
    int other_target = 6 - (pos + target);
    if (disk == 1) {
        cout << pos << " " << target << "\n";
        return;
    }
    move(disk - 1, pos, other_target);
    cout << pos << " " << target << "\n";
    move(disk - 1, other_target, target);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    cout << (1 << n) - 1 << "\n";
    move(n, 1, 3);
}
