#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (0)
#endif

// clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
template<uint32_t m> struct modint {
    static_assert(m >= 1, "Modulus must be in the range [1;2^31)");

    using mint = modint;

  public:
    static constexpr uint32_t mod() noexcept { return m; }
    constexpr modint() noexcept = default;
    constexpr modint(int64_t v) noexcept : _v((v %= m) < 0 ? v + m : v) {}
    constexpr static mint raw(uint32_t v) noexcept { mint x; return x._v = v, x; }
    template<class T> constexpr explicit operator T() const noexcept { return _v; }

    constexpr mint &operator++() noexcept { return _v = ++_v == mod() ? 0 : _v, *this; }
    constexpr mint &operator--() noexcept { --(_v ? _v : _v = mod()); return *this; }
    constexpr mint operator++(int) noexcept { return exchange(*this, ++mint(*this)); }
    constexpr mint operator--(int) noexcept { return exchange(*this, --mint(*this)); }

    constexpr mint &operator+=(mint rhs) noexcept {
        return _v = int(_v += rhs._v - mod()) < 0 ? _v + mod() : _v, *this;
    }
    constexpr mint &operator-=(mint rhs) noexcept {
        return _v = int(_v -= rhs._v) < 0 ? _v + mod() : _v, *this;
    }
    constexpr mint &operator*=(mint rhs) noexcept {
        return _v = uint64_t(_v) * rhs._v % mod(), *this;
    }
    constexpr mint &operator/=(mint rhs) noexcept {
        return *this = *this * rhs.inv();
    }

    constexpr friend mint operator+(mint l, mint r) noexcept { return l += r; }
    constexpr friend mint operator-(mint l, mint r) noexcept { return l -= r; }
    constexpr friend mint operator*(mint l, mint r) noexcept { return l *= r; }
    constexpr friend mint operator/(mint l, mint r) noexcept { return l /= r; }

    constexpr mint operator+() const noexcept { return *this; }
    constexpr mint operator-() const noexcept { return raw(_v ? mod() - _v : 0); }

    constexpr friend bool operator==(const mint &l, const mint &r) noexcept { return l._v == r._v; }
    constexpr friend bool operator!=(const mint &l, const mint &r) noexcept { return l._v != r._v; }
    constexpr friend bool operator<(const mint &l, const mint &r) noexcept { return l._v < r._v; }

    constexpr mint pow(uint64_t n) const noexcept {
        mint b = *this, res = 1;
        while (n) n & 1 ? res *= b : 0, b *= b, n >>= 1;
        return res;
    }

    constexpr mint inv() const noexcept {
        int a = _v, b = mod(), x = 1, y = 0;
        while (b) {
            x = exchange(y, x - a / b * y);
            a = exchange(b, a % b);
        }
        assert(a == 1);
        return x;
    }

    friend istream &operator>>(istream &is, mint &x) {
        int64_t v{};
        return is >> v, x = v, is;
    }
    friend ostream &operator<<(ostream &os, const mint &x) { return os << x._v; }

  private:
    uint32_t _v = 0;
};
using modint107 = modint<1'000'000'007>;
using modint998 = modint<998'244'353>;
#pragma GCC diagnostic pop
// clang-format on

using i64 = int64_t;

template<class T> auto fwht(vector<T> &a) {
    int n = int(a.size());
    for (int w = 1; w < n; w *= 2) {
        for (int i = 0; i < n; i += 2 * w) {
            for (int j = i; j < i + w; j++) {
                T x = a[j], y = a[j | w];
                a[j] = x + y;
                a[j | w] = x - y;
            }
        }
    }
}
template<class T> auto ifwht(vector<T> &a) {
    int n = int(a.size());
    T inv2 = T(1) / 2;
    for (int w = 1; w < n; w *= 2) {
        for (int i = 0; i < n; i += 2 * w) {
            for (int j = i; j < i + w; j++) {
                T x = a[j], y = a[j | w];
                a[j] = (x + y) * inv2;
                a[j | w] = (x - y) * inv2;
            }
        }
    }
}
template<class T> auto xor_convolve(vector<T> a, vector<T> b) {
    fwht(a), fwht(b);
    for (int i = 0; i < a.size(); i++) a[i] *= b[i];
    ifwht(a);
    return a;
}

const int MX = 1 << 20;
using mint = modint998;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int pref = 0;
    bool f = false;
    vector<mint> a(MX);
    a[0] = 1;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        pref ^= x;
        f |= int(a[pref]);
        a[pref] = 1;
    }
    auto c = xor_convolve(a, a);
    vector<int> res;
    for (int i = 0; i < MX; i++)
        if ((i == 0 && f) || (i != 0 && c[i])) res.push_back(i);
    int k = int(res.size());
    cout << k << "\n";
    for (int i = 0; i < k; i++) cout << res[i] << " \n"[i == k - 1];
}
