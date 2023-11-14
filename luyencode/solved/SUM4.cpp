#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << fixed << setprecision(8);

    int c;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;

        cout << 2 - 2 / (double)(input + 1) << "\n";
    }

    return 0;
}
