#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    getline(cin, str);

    for (int i = 0; i < str.length(); i++) {
        if (str[i] < 'a' && str[i] >= 'A') {
            cout << (char)(str[i] + 32);
        } else {
            cout << str[i];
        }
    }

    return 0;
}
