#ifdef READ_MAIN

void solve() {

}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}

#else
#define READ_MAIN

#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;
template<class T> using vec = vector<T>;
template<class Con> inline int len(const Con &c) { return int(c.size()); }
#define all(a) begin(a), end(a)
#define pb push_back
#define eb emplace_back
#define pp pop_back

// clang-format off
template<class... Ts> inline void read(Ts &&...args) { ((cin >> args), ...); }
template<class... Ts> inline void print(Ts &&...args) { ((cout << args << " "), ...); }
template<class... Ts> inline void println(Ts &&...args) { ((cout << args << " "), ...), cout << "\n"; }
#define rd(ty, ...) ty __VA_ARGS__; read(__VA_ARGS__)
// clang-format on

#ifndef LOCAL
#define dbg(...) 42
#define mark_dbg() if (false)
#endif

#include __FILE__
#endif
