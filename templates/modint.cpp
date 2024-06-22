#include <cassert>
#include <cstdint>
#include <istream>
#include <utility>
using namespace std;

// clang-format off
template<uint32_t m> struct modint {
    static_assert(int(m) >= 1, "Modulus must be in the range [1;2^31)");

    using mint = modint;

  public:
    static constexpr uint32_t mod() { return m; }
    modint() : _v(0) {}
    modint(int64_t v) : _v((uint32_t)((v %= m) < 0 ? v + m : v)) {}
    static mint raw(uint32_t v) { return *reinterpret_cast<mint *>(&v); }
    template<class T> constexpr explicit operator T() const { return _v; }

    constexpr mint &operator++() {
        _v++;
        if (_v == mod()) _v = 0;
        return *this;
    }
    constexpr mint &operator--() {
        if (_v == 0) _v = mod();
        _v--;
        return *this;
    }
    constexpr mint operator++(int) { return exchange(*this, ++mint(*this)); }
    constexpr mint operator--(int) { return exchange(*this, --mint(*this)); }

    constexpr mint &operator+=(const mint &rhs) {
        _v += rhs._v;
        if (_v >= mod()) _v -= mod();
        return *this;
    }
    constexpr mint &operator-=(const mint &rhs) {
        _v += mod() - rhs._v;
        if (_v >= mod()) _v -= mod();
        return *this;
    }
    constexpr mint &operator*=(const mint &rhs) {
        return _v = int(uint64_t(_v) * rhs._v % mod()), *this;
    }
    constexpr mint &operator/=(const mint &rhs) {
        return *this = *this * rhs.inv();
    }

    constexpr friend mint operator+(mint l, const mint &r) { return l += r; }
    constexpr friend mint operator-(mint l, const mint &r) { return l -= r; }
    constexpr friend mint operator*(mint l, const mint &r) { return l *= r; }
    constexpr friend mint operator/(mint l, const mint &r) { return l /= r; }

    friend mint operator==(const mint &l, const mint &r) {
        return l._v == r._v;
    }
    friend mint operator!=(const mint &l, const mint &r) {
        return l._v != r._v;
    }

    constexpr mint pow(int64_t n) const {
        mint b = *this, res(1);
        while (n) n & 1 ? res *= b : 0, b *= b, n >>= 1;
        return res;
    }

    constexpr mint inv() const {
        int a = _v, b = mod(), x = 1, y = 0;
        while (a) {
            y = exchange(x, y - b / a * x);
            b = exchange(a, b % a);
        }
        assert(b == 1);
        return y;
    }

    constexpr mint operator+() const { return *this; }
    constexpr mint operator-() const { return raw(_v ? mod() - _v : 0); }

    friend istream &operator>>(istream &is, mint &x) {
        int64_t v{};
        return is >> v, x = v, is;
    }
    friend ostream &operator<<(ostream &os, const mint &x) { return os << x._v; }

  private:
    uint32_t _v;
};
// clang-format on
