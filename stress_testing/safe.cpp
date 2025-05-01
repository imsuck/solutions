#include <bits/stdc++.h>
#define newl '\n'

const int N = 2e5 + 10;
const int V = 1e7 + 10;
const long long INF = 1e18;
const long long M = 1e9 + 7;

long long a[N + 1], b[N + 1];
int n, q;
long long diff[N + 1], f[N + 1];

void readData() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        if (i > 1) {
            diff[i - 1] = a[i] - a[i - 1];
        }
    }
}
long long calc() {
    std::vector<long long> b;
    b.emplace_back(0);
    b.emplace_back(a[1]);
    int it = 2;
    for (int i = 2; i < n; ++i) {
        if ((a[i - 1] <= a[i]) != (a[i] <= a[i + 1])) {
            //            std::cerr << i << newl;4
            it = std::max(it, i - 1);
            while (it <= std::min(n, i + 1)) {
                b.emplace_back(a[it]);
                ++it;
            }
        }
    }
    it = std::max(it, n);
    while (it <= n) {
        b.emplace_back(a[it++]);
    }
    //    for(int val : b){
    //        std::cout << val << " ";
    //    }
    //    std::cout << newl;
    for (int i = 1; i < (int)b.size(); ++i) {
        f[i] = 0;
        long long mx = b[i], mn = b[i];
        for (int j = i; j >= 1 && i - j + 1 <= 4; --j) {
            mx = std::max(mx, (long long)b[j]);
            mn = std::min(mn, (long long)b[j]);
            f[i] = std::max(f[i], f[j - 1] + mx - mn);
        }
    }
    return f[(int)b.size() - 1];
}
void update(long long &ans, int i, int x) {
    if (i > 1 && i < n) {
        if ((diff[i - 1] < 0) != (diff[i] < 0)) {
            ans += std::min(abs(diff[i - 1]), abs(diff[i]));
        }
    }
    if (i < n - 1) {
        if ((diff[i] < 0) != (diff[i + 1] < 0)) {
            ans += std::min(abs(diff[i]), abs(diff[i + 1]));
        }
    }
    if (i < n && i > 0) {
        ans -= abs(diff[i]);
    }
    diff[i] += x;
    if (i < n && i > 0) {
        ans += abs(diff[i]);
    }
    if (i > 1 && i < n) {
        if ((diff[i - 1] < 0) != (diff[i] < 0)) {
            ans -= std::min(abs(diff[i - 1]), abs(diff[i]));
        }
    }
    if (i < n - 1) {
        if ((diff[i] < 0) != (diff[i + 1] < 0)) {
            ans -= std::min(abs(diff[i]), abs(diff[i + 1]));
        }
    }
}
void solve() {
    long long ans = 0;
    for (int i = 1; i < n; ++i) {
        if (i < n - 1 && (diff[i] < 0) != (diff[i + 1] < 0)) {
            ans -= std::min(abs(diff[i]), abs(diff[i + 1]));
        }
        ans += abs(diff[i]);
    }
    //    std::cout << ans << newl;
    for (int i = 1; i <= q; ++i) {
        int l, r, x;
        std::cin >> l >> r >> x;
        for (int j = l; j <= r; ++j) {
            a[j] += x;
        }
        //        update(ans,l - 1,x);
        //        update(ans,r,-x);
        //        assert(calc() == ans);
        std::cout << calc() << newl;
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    readData();
    solve();
    return 0;
}
