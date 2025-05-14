// O(nlog(n))
// too lazy to think
#include <bits/stdc++.h>
using namespace std;

template<class T> bool chmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;

    vector<int> a(n), t(2 * n);
    map<int, pair<int, vector<int>>> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        t[i + n] = i;
        mp[a[i]].second.push_back(i);
    }

    auto amax = [&](int i, int j) {
        return a[i] > a[j] || (a[i] == a[j] && i < j) ? i : j;
    };
    auto pull = [&](int p) { t[p] = amax(t[p << 1], t[p << 1 | 1]); };
    auto get = [&](int l, int r) {
        int ret = l;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret = amax(ret, t[l++]);
            if (r & 1) ret = amax(t[--r], ret);
        }
        return ret;
    };
    for (int i = n; --i;) pull(i);

    auto rec = [&](auto &f, int l, int r) -> int {
        if (l > r - 1) return 0;
        if (l == r - 1) {
            mp[a[l]].first++;
            return 1;
        }

        int ret = 1;
        int mxi = get(l, r);
        auto &[ptr, pos] = mp[a[mxi]];
        if (pos.size() == 1) {
            chmax(ret, f(f, l, pos[0]) + 1);
            chmax(ret, f(f, pos[0] + 1, r) + 1);
            return ret;
        }

        for (bool fl = 0; ptr < pos.size() && pos[ptr] < r; ptr++) {
            if (!fl) {
                chmax(ret, f(f, l, pos[ptr]) + 1);
                fl = 1;
            }
            if (ptr + 1 < pos.size()) {
                chmax(ret, f(f, pos[ptr] + 1, min(r, pos[ptr + 1])) + 1);
            } else {
                chmax(ret, f(f, max(l, pos[ptr] + 1), r) + 1);
            }
        }
        return ret;
    };

    cout << rec(rec, 0, n) << "\n";
}
