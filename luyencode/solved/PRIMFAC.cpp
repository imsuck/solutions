#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    map<long long, long long> list;

    while (n % 2 == 0) {
        list[2]++;
        n /= 2;
    }

    for (int i = 3; i <= sqrt(n);) {
        if (n % i == 0) {
            list[i]++;
            n /= i;
        } else {
            i += 2;
        }
    }
    if (n != 1) {
        list[n]++;
    }

    if (list.empty()) {
        cout << "0";
        return 0;
    }

    cout << list.size() << "\n";
    for (auto const &[k, v] : list) {
        cout << k << " " << v << "\n";
    }

    return 0;
}
