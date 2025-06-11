#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (0)
#endif

template<class T> constexpr T inf = numeric_limits<T>::max();

void solve() {
    int n, q;
    string s;
    cin >> n >> q >> s;

    vector<pair<char, char>> qs(q);
    map<pair<char, char>, int> m, m2;
    for (int i = 0; i < q; i++) {
        cin >> qs[i].first >> qs[i].second;

        if (qs[i] == pair('b', 'a')) {
            if (m[{'c', 'b'}]) {
                m2[{'c', 'a'}]++, m[{'c', 'b'}]--;
            } else {
                m[{'b', 'a'}]++;
            }
        } else if (qs[i] == pair('c', 'a')) {
            if (m[{'b', 'c'}]) {
                m2[{'b', 'a'}]++, m[{'b', 'c'}]--;
            } else {
                m[{'c', 'a'}]++;
            }
        } else {
            m[qs[i]]++;
        }
    }

    for (char &c : s) {
        if (c == 'b') {
            if (m[{'b', 'a'}]) {
                m[{'b', 'a'}]--;
                c = 'a';
            } else if (m2[{'c', 'a'}]) {
                m2[{'c', 'a'}]--, m[{'c', 'b'}]++;
                c = 'a';
            } else if (m2[{'b', 'a'}]) {
                m2[{'b', 'a'}]--;
                c = 'a';
            }
        } else if (c == 'c') {
            if (m[{'c', 'a'}]) {
                m[{'c', 'a'}]--;
                c = 'a';
            } else if (m2[{'b', 'a'}]) {
                m2[{'b', 'a'}]--;
                c = 'a';
            } else if (m2[{'c', 'a'}]) {
                m2[{'c', 'a'}]--;
                c = 'a';
            } else if (m[{'c', 'b'}]) {
                m[{'c', 'b'}]--;
                c = 'b';
            }
        }
    }
    cout << s << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
