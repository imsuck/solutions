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

i64 n, tot = 0, mn = 1e18;
i64 p[20];

void solve(i32 i, i64 s) {
    if (i == n) {
        mn = min(mn, abs(tot - 2 * s));
        return;
    }
    solve(i + 1, s);
    solve(i + 1, s + p[i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (i32 i = 0; i < n; i++) {
        cin >> p[i];
        tot += p[i];
    }
    solve(0, 0);
    cout << mn << "\n";
}
