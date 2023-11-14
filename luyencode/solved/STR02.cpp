#include <bits/stdc++.h>
using namespace std;

int main() {
    string t;
    getline(cin, t);

    for (int i = 0; i <= stoi(t); i++) {
        string str;
        getline(cin, str);

        for (int i = 0; i < str.length(); i++) {
            char c;
            if (str[i] <= 'Z' && str[i] >= 'A') {
                c = (char)(str[i] + 32);
            } else {
                c = str[i];
            }
            if (str[i] <= 'z' && str[i] >= 'a' &&
                (i == 0 || i != 0 && str[i - 1] == ' ')) {
                c -= 32;
            }
            cout << c;
        }
        cout << "\n";
    }

    return 0;
}
