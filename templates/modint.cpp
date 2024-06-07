#include <cassert>
#include <cstdint>
#include <utility>
using namespace std;

template <int m> struct modint {
    static_assert(m >= 1);

    using mint = modint;

  public:
    static constexpr int mod() { return m; }
    modint() : _v(0) {}
    modint(int64_t v) {
        if (v < 0 || mod() <= v)
            v %= mod();
        _v = v + (v < 0) * mod();
    }
    static constexpr mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    mint &operator++() {
        _v++;
        if (_v == mod())
            _v = 0;
        return *this;
    }
    mint &operator--() {
        if (_v == 0)
            _v = mod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint tmp=*this;
        ++*this;
        return tmp;
    }
    mint operator--(int) {
        mint tmp=*this;
        --*this;
        return tmp;
    }

    mint &operator+=(const mint &rhs) {
        _v += rhs._v;
        if (_v >= mod())
            _v -= mod();
        return *this;
    }
    mint &operator-=(const mint &rhs) {
        _v += mod() - rhs._v;
        if (_v >= mod())
            _v -= mod();
        return *this;
    }
    mint &operator*=(const mint &rhs) {
        _v = int(uint64_t(_v) * rhs._v % mod());
        return *this;
    }
    mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

    friend mint operator+(const mint &lhs, const mint &rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint &lhs, const mint &rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint &lhs, const mint &rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint &lhs, const mint &rhs) {
        return mint(lhs) /= rhs;
    }
    friend mint operator==(const mint &lhs, const mint &rhs) {
        return lhs._v == rhs._v;
    }
    friend mint operator!=(const mint &lhs, const mint &rhs) {
        return lhs._v != rhs._v;
    }

    mint pow(int64_t n) const {
        assert(n >= 0);
        mint b=*this, res(1);
        while (n)
            n & 1 ? res *= b : 0, b *= b, n >>= 1;
        return res;
    }

    mint inv() const {
        int a = _v, b = mod(), x = 1, y = 0;
        while (a) {
            y = exchange(x, y - b / a * x);
            b = exchange(a, b % a);
        }
        assert(b == 1);
        return mint(y);
    }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    operator unsigned int() const { return _v; }

  private:
    int _v;
};
