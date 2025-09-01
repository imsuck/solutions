#include <bits/stdc++.h>
using namespace std;
#include "library/other/types.hpp"

void solve() {
    i32 n;
    cin >> n;
    list<i32> a(n);
    iota(begin(a), end(a), 1);
    auto nxt = [&](auto it) { return ++it == end(a) ? begin(a) : it; };
    for (auto it = begin(a); a.size();) {
        it = nxt(it);
        cout << *it << " \n"[a.size() == 1];
        a.erase(exchange(it, nxt(it)));
    }
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
