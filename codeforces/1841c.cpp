#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using str = string;
#define vec vector

map<char, i64> conv = {
    {'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}, {'E', 10000}};

void solve() {
    str s;
    cin >> s;
    i64 sum = 0;
    char mx = 'A', fne = -1;
    bool all_same = true;
    for (i32 i = s.size() - 1; i >= 0; i--) {
        if (i - 1 >= 0 && s[i] != s[i - 1]) {
            all_same = false;
        }
        if (fne == -1 && s[i] != 'E') {
            fne = i;
        }
        mx = max(mx, s[i]);
        if (s[i] < mx) {
            sum -= conv[s[i]];
        } else {
            sum += conv[s[i]];
        }
    }
    if (!all_same && s[0] != 'E')
        sum += conv['E'] - conv[s[fne]];
    cout << sum << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
