#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 n, x, a;
    cin >> n >> x;
    map<i32, i32> m;
    for (i32 i = 1; i <= n; i++) {
        cin >> a;
        if (m.count(x - a)) {
            cout << m[x-a] << " " << i << "\n";
            return 0;
        }
        m[a] = i;
    }
    cout << "IMPOSSIBLE\n";
}
