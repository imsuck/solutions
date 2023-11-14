#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, palindrome = "";
    map<char, int> m;
    map<char, string> ss;
    bool odd_exists = false;
    char odd_char = ' ';
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        m[s[i]] += 1;
    }
    for (auto x : m) {
        if (x.second % 2 != 0 && !odd_exists) {
            odd_exists = true;
            odd_char = x.first;
            palindrome = string(x.second, odd_char);
        } else if (x.second % 2 != 0 && odd_exists) {
            cout << "NO SOLUTION";
            return 0;
        }
        ss[x.first] = string(x.second / 2, x.first);
    }
    for (auto x : ss) {
        if (x.first == odd_char) {
            continue;
        }
        palindrome = x.second + palindrome + x.second;
    }
    cout << palindrome;
}
