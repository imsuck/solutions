#include <bits/stdc++.h>
using namespace std;

double calc(int n) {
    int a = 1, b = 1;
    for (int i = 0; i < n; i++) {
        a += b;
        swap(a, b);
    }
    return (double)a / b;
}

int main() {
    cout << fixed << setprecision(5);
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        cout << calc(n) << "\n";
    }

    return 0;
}
