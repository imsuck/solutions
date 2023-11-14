#include <bits/stdc++.h>
using namespace std;

int main() {
    int c;
    cin >> c;
    int list[c];

    for(int i = 0; i < c; i++) {
        int input;
        cin >> input;
        list[i] = input;
    }

    std::sort(list, list + sizeof(list) / sizeof(list[0]));

    for(int i = c - 1; i >= 0; i--) {
        cout << list[i] << " ";
    }

    return 0;
}
