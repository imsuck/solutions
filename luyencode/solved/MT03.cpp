#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s = 0;
    cin >> n;

    for (int i = 0; i < n * n; i++) {
        int input;
        cin >> input;
        if (i % (n + 1) == 0) {
            s += input;
        }
    }

    cout << s;

    return 0;
}
