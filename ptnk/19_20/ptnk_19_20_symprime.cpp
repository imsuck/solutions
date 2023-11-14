#include <bits/stdc++.h>
using namespace std;

const int N = 2e7 + 2;

int p[N];
vector<int> a;

void sieve() {
    fill(p, p + N, 0);
    p[0] = -1;
    p[1] = -1;
    for (long long i = 2; i < N; i++) {
        if (p[i] == 0) {
            if (i * i < N)
                for (long long j = i * i; j < N; j += i)
                    p[j] = -1;

            a.push_back(i);
            p[i] = a.size() - 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        if (p[n] > 0 && n > 2) {
            int lhs = a[p[n] - 1], rhs = a[p[n] + 1];
            if (n == (lhs + rhs) / 2)
                cout << "YES\n";
            else
                cout << "NO\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
