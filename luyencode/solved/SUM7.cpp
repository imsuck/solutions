#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(5);

    int c;
    cin >> c;
    float memo[1000000];

    for (int i = 0; i < 1000000; i++) {
        memo[i] = sqrt(i + 1 + memo[i - 1]);
    }

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;
        cout << memo[input - 1] << "\n";
    }

    return 0;
}
