// Source: Tin hoc tre B THCS Da Nang 2021-2022
// Problem statement: A number is super symmetric if it only contains one kind
// digit ie. 111, 2, 88888, etc.
// Given a positive integer x, find the smallest positive integer y such that
// x + y is super symmetric.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n;
    cin >> n;

    if (n.size() == 1) {
        cout << "1\n";
        return 0;
    }
    if (n == "9") {
        cout << "2\n";
        return 0;
    }
    char init = n[0];
    for (int i = 1; i < n.size(); i++) {
        if (n[i] < init) {
            unsigned long long num = stoull(string(n.size(), n[0]));
            cout << num - stoull(n) << "\n";
            return 0;
        } else if (n[i] > init) {
            unsigned long long num = stoull(string(n.size(), n[0] + 1));
            cout << num - stoull(n) << "\n";
            return 0;
        }
    }

    if (init != '9') {
        cout << string(n.size(), '1') << "\n";
    } else {
        string num = string(n.size(), '1');
        num.back() = '2';
        cout << num << "\n";
    }

    return 0;
}
