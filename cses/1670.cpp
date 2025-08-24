#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto

fn solve() {
    using arr = array<i32, 9>;
    auto to_i32 = [&](const arr &a) {
        i32 r = 0;
        for (i32 i : a) r = 10 * r + i;
        return r;
    };
    auto to_arr = [&](i32 x) {
        arr a;
        for (i32 i = 8; i >= 0; i--, x /= 10) a[i] = x % 10;
        return a;
    };
    unordered_map<i32, i32> d;
    arr st;
    for (i32 &i : st) cin >> i;
    queue<i32> q;
    d[to_i32(st)] = 0, q.push(to_i32(st));
    while (q.size()) {
        i32 cur = q.front();
        q.pop();
        if (cur == 123456789) {
            cout << d[123456789] << "\n";
            return;
        }
        auto cd = d[cur];
        auto try_add = [&](i32 x) {
            if (d.count(x)) return;
            d[x] = cd + 1;
            q.push(x);
        };
        auto try_fr = [&](i32 i, i32 j) {
            swap(st[i], st[j]);
            try_add(to_i32(st));
            swap(st[i], st[j]);
        };
        st = to_arr(cur);
        // horiz
        try_fr(0, 1);
        try_fr(1, 2);
        try_fr(3, 4);
        try_fr(4, 5);
        try_fr(6, 7);
        try_fr(7, 8);
        // vert
        try_fr(0, 3);
        try_fr(3, 6);
        try_fr(1, 4);
        try_fr(4, 7);
        try_fr(2, 5);
        try_fr(5, 8);
    }
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
