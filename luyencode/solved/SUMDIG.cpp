#include <bits/stdc++.h>
#include <cstddef>
#include <string>
using namespace std;

long sum_dig(string s) {
    long sum = 0;
    for (int i = 0; i < s.length(); i++) {
        sum += s[i] - '0';
    }

    return sum;
}

int main() {
    int c;
    cin >> c;

    for (int i = 0; i < c; i++) {
        string input;
        cin >> input;

        cout << sum_dig(input) << "\n";
    }

    return 0;
}
