#include <bits/stdc++.h>
using namespace std;

int cnt[5005] = {0};

void preprocess() {
    for (int a = 1; a < 5000; a++) {
        for (int b = a + 1; b < 5000; b++) {
            int cc = a * a + b * b;
            int c = sqrt((long double)cc);
            if (a + b + c > 5000)
                break;
            if (c * c == cc) // Check if c is an integer
                cnt[a + b + c]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    preprocess();

    while (t--) {
        int p;
        cin >> p;

        cout << cnt[p] << "\n";
    }

    return 0;
}
