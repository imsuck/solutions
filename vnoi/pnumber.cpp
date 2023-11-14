#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 2;

bool sieve[MAX];

void era() {
    fill(sieve, sieve + MAX, true);
    sieve[0] = false;
    sieve[1] = false;
    for (int i = 2; i * i < MAX; i++)
        if (sieve[i])
            for (int j = i * i; j < MAX; j += i)
                sieve[j] = false;
}

int main() {
    era();

    int a, b;
    cin >> a >> b;

    for (int i = a; i <= b; i++)
        if (sieve[i])
            cout << i << "\n";

    return 0;
}
