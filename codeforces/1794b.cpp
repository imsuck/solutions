#include <bits/stdc++.h>
using namespace std;

void solve(int n) {
    int last, current, llast;
    cin >> current;
    if (current == 1) {
        current = 2;
    }
    for (int i = 0; i < n - 1; i++) {
        llast = last;
        last = current;
        cin >> current;

        if (llast == 2 && last == 1)
            last = 3;
        else if (last == 1)
            last = 2;
        while (current % last == 0)
            current++;

        cout << last << " ";
    }
    cout << current << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        solve(n);
    }

    return 0;
}
