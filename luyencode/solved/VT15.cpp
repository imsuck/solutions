#include <bits/stdc++.h>
using namespace std;

int main() {
    int c, max = INT32_MIN, max2 = INT32_MIN, max3 = INT32_MIN, min = INT32_MAX,
           min2 = INT32_MAX, min3 = INT32_MAX;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;

        if (max < input) {
            max3 = max2;
            max2 = max;
            max = input;
        } else if (max2 < input) {
            max3 = max2;
            max2 = input;
        } else if (max3 < input) {
            max3 = input;
        }

        if (min > input) {
            min3 = min2;
            min2 = min;
            min = input;
        } else if (min2 > input) {
            min3 = min2;
            min2 = input;
        } else if (min3 > input) {
            min3 = input;
        }
    }

    cout << std::max(max * max2 * max3, max * min * min2);

    return 0;
}
