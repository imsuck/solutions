#include "bits/stdc++.h"
using namespace std;

ostream cnull(nullptr);
#ifndef LOCAL
#define cerr cnull
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    str s;
    cin >> s;
    if (s[0] - '0' >= 5) {
        cout << "1" + string(s.len(), '0') << "\n";
        return;
    }
    for (i32 i = 0; i < s.len(); i++) {
        if (s[i] >= '5') {
            i32 j = i - 1;
            for (; j >= 0; j--) {
                s[j]++;
                if (s[j] < '5') {
                    break;
                }
            }
            for (j++; j < s.len(); j++) {
                s[j] = '0';
            }
            break;
        }
    }
    if (s == string(s.len(), '0')) {
        cout << 1 << s << "\n";
    } else {
        cout << s << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
