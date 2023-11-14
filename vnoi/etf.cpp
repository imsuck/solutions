#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 5;

vector<int> phi(MAX);

void preprocess() {
    for (int i = 0; i < MAX; i++)
        phi[i] = i;

    for (int i = 2; i < MAX; i++)
        if (phi[i] == i)
            for (int j = i; j < MAX; j += i)
                phi[j] -= phi[j] / i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    preprocess();

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        cout << phi[n] << "\n";
    }

    return 0;
}
