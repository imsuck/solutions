#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b, out = "";
    int carry = 0;
    cin >> a >> b;
    while (a.length() < b.length()) {
        a = "0" + a;
    }
    while (a.length() > b.length()) {
        b = "0" + b;
    }

    for (int i = a.length() - 1; i >= 0; i--) {
        int an = a[i] - '0', bn = b[i] - '0';
        int n = an + bn + carry;

        out = to_string(n % 10) + out;

        carry = n / 10;
    }
    if (carry == 1) {
        out = "1" + out;
    }

    cout << out;

    return 0;
}
