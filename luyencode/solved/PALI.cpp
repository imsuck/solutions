#include <bits/stdc++.h>
using namespace std;

bool is_palindrome(long x) {
    int len = log10(x);
    long flipped = 0;
    for (int i = len; i >= 0; i--) {
        flipped += long(x / pow(10, i)) % 10 * pow(10, len - i);
    }
    if (x == flipped) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        long a;
        cin >> a;
        if (is_palindrome(a)) {
            cout << a << " ";
        }
    }

    return 0;
}
