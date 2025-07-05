#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;
template<class T> using vec = vector<T>;

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 t = 1;
    cin >> t;
    while (t--) {
        i32 n, m;
        i64 k;
        cin >> n >> m >> k, n--, m--;
        i64 x = k, y = k;
        i32 px = i32(x / n % 2);
        x = px == 0 ? x % n : n - x % n;
        i32 py = i32(y / m % 2);
        y = py == 0 ? y % m : m - y % m;
        cout << x + 1 << " " << y + 1 << " "
             << k / n + k / m - k / lcm<u64>(n, m) << "\n";
    }
}
