#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (0)
#endif

using i64 = int64_t;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    multiset<int> avail;
    while (k--) avail.insert(0);

    vector<pair<int, int>> evs(n);
    for (auto &[l, r] : evs) cin >> l >> r;
    sort(begin(evs), end(evs), [](auto a, auto b) {
        return a.second < b.second;
    });

    int cnt = 0;
    for (auto [l, r] : evs) {
        auto candidate = avail.upper_bound(l);
        if (candidate == avail.begin()) continue;
        avail.erase(--candidate), avail.insert(r);
        cnt++;
    }
    cout << cnt << "\n";
}
