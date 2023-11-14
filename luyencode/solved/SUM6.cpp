#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(5);
    int c;
    cin >> c;
    double memo[10000];

    for (int i = 0; i < 10000; i++) {
        if (i != 0) {
            memo[i] = sqrt(2 + memo[i - 1]);
        } else {
            memo[i] = sqrt(2);
        }
    }

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;

        cout << memo[input - 1] << "\n";
    }

    return 0;
}
