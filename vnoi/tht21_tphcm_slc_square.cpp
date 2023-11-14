#include <bits/stdc++.h>
using namespace std;

long long power(long long a, long long n) {
    long long res = 1;
    while (n > 0) {
        res = (n & 1) ? res * a : res;
        n >>= 1;
        a = a * a;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c;
    long long res = 1;
    cin >> a >> b >> c;
    map<int, int> p;

    int x = 2, count;
    while (a > 1) {
        count = 0;
        while (a % x == 0) {
            count++;
            a /= x;
        }
        p[x] = max(p[x], count);
        x++;
    }
    x = 2;
    while (b > 1) {
        count = 0;
        while (b % x == 0) {
            count++;
            b /= x;
        }
        p[x] = max(p[x], count);
        x++;
    }
    x = 2;
    while (c > 1) {
        count = 0;
        while (c % x == 0) {
            count++;
            c /= x;
        }
        p[x] = max(p[x], count);
        x++;
    }

    for (pair<int, int> pr : p) {
        res *= power(pr.first, (pr.second + 1) / 2);
    }

    cout << res << "\n";

    return 0;
}
