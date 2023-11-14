#include <bits/stdc++.h>
#include <cmath>
using namespace std;

int main() {
    int c;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int input, count = 0;
        cin >> input;

        for (int j = 1; j <= sqrt(input); j++) {
            if (input % j == 0) {
                if (j * j == input) {
                    count -= j;
                }
                count += j + input / j;
            }
        }

        cout << count << "\n";
    }

    return 0;
}
