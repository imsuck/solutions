#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    int size = m * n;
    int arr[size];

    for (int i = 0; i < size; i++) {
        int input;
        cin >> input;
        cout << input << " ";
        if ((i + 1) % n == 0) {
            cout << "\n";
        }
    }

    return 0;
}
