#include <bits/stdc++.h>
using namespace std;

float calc(int numb, int count) {
    if (count == numb) {
        return sqrt(numb);
    }
    return sqrt(count + calc(numb, count + 1));
}

int main() {
    cout << fixed << setprecision(5);

    int c;
    cin >> c;
    float memo[1000];

    for (int i = 0; i < 1000; i++) {
        memo[i] = calc(i + 1, 1);
    }

    for (int i = 0; i < c; i++) {
        int input;
        cin >> input;
        cout << memo[input - 1] << "\n";
    }

    return 0;
}
