#include <bits/stdc++.h>
using namespace std;

int main() {
    int c, first, last;
    cin >> c;
    int a[c - 2];
    cin >> first;
    cout << first << " ";

    for(int i = 0; i < c - 2; i++) {
        int input;
        cin >> input;
        a[i] = input;
    }

    sort(a, a + c - 2);

    for(int i = 0; i < c - 2; i++) {
        cout << a[i] << " ";
    }

    cin >> last;
    cout << last;

    return 0;
}
