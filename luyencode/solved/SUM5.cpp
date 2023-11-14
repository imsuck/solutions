#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(5);
    int T;
    cin >> T;

    double memo[1000000];
    memo[1] = 1;
    for (int i = 2; i <= 100000; i++) {
        memo[i] = memo[i - 1] + (double)1 / i;
    }

    for (int i = 1; i <= T; i++) {
        int n;
        cin >> n;
        cout << memo[n] << "\n";
    }

    return 0;
}
