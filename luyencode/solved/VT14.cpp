#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

int main() {
    int c, max = INT32_MIN, max2 = INT32_MIN, min = INT32_MAX, min2 = INT32_MAX;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;

        if (max < input) {
            max2 = max;
            max = input;
        } else if (max2 < input) {
            max2 = input;
        }
        if (min > input) {
            min2 = min;
            min = input;
        } else if (min2 > input) {
            min2 = input;
        }
    }

    cout << std::max(max * max2, min * min2);

    return 0;
}
