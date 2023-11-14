#include <bits/stdc++.h>
using namespace std;

bool validate(string s) {
    int unpair = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            unpair += 1;
        } else if (s[i] == ')') {
            unpair -= 1;
        }
    }
    return unpair == 0;
}
int unmatched_count(string s) {
    int open_count = 0;
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            open_count += 1;
        } else if (s[i] == ')') {
            if (open_count <= 0) {
                count += 1;
            } else {
                open_count -= 1;
            }
        }
    }
    return count;
}

int sol(string s) {
    int unpair = 0;
    int uc = unmatched_count(s);
    if (uc == 0) {
        return 0;
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            unpair += 1;
        } else if (s[i] == ')') {
            unpair -= 1;
        }
        if (unpair == -uc) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    getline(cin, s);

    if (!validate(s)) {
        cout << "-1";
        return 0;
    }
    cout << sol(s);

    return 0;
}
