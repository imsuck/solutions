#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int BOUND = 19;

ull ten_exp(ull n) {
    ull res = 1;
    for (int i = 0; i < n; i++)
        res *= 10;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ull lim[BOUND];
    lim[0] = 0;
    for (int i = 1; i < BOUND; i++)
        lim[i] = lim[i - 1] + i * (ten_exp(i) - ten_exp(i - 1));

    int q;
    ull k;
    cin >> q;

    for (int i = 0; i < q; i++) {
        cin >> k;
        if (k < 10) {
            cout << k << "\n";
            continue;
        }
        auto it = lower_bound(lim, lim + BOUND, k);
        ull fix = k - *(it - 1);
        ull idx = it - lim;
        char digit =
            to_string(ten_exp(idx - 1) + (fix - 1) / idx)[(fix - 1) % idx];
        cout << digit << "\n";
    }

    return 0;
}
