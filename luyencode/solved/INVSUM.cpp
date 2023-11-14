#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(5);

    int T;
    cin >> T;
    double solutions[1000001];
    solutions[1] = 1;

    for (int i = 2; i < 1000001; i++) {
        solutions[i] = solutions[i - 1] + 1.0 / (2 * i - 1);
    }

    for (int i = 0; i < T; i++) {
        int n;
        cin >> n;
        cout << solutions[n] << "\n";
    }

    return 0;
}
