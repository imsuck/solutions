#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
    if (n < 2) {
        return false;
    } else if (n == 2) {
        return true;
    }

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int c, max;
    unordered_map<int, int> list;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int temp;
        cin >> temp;
        max = std::max(max, temp);

        if (is_prime(temp)) {
            list[temp] = 69420;
        }
    }

    for (int i = 0; i <= max; i++) {
        if (list[i] == 69420) {
            cout << i << " ";
        }
    }

    return 0;
}
