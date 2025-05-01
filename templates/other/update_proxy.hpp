// clang-format off
template<class T, class Cb> struct UpdateProxy {
    T &x;
    Cb cb;

    UpdateProxy(T &_x, Cb _cb) : x(_x), cb(_cb) {}

    operator T() const { return x; }
    auto &operator++() && { x++, cb(); return *this; }
    auto &operator--() && { x--, cb(); return *this; }
    auto &operator+=(const T &r) && { x += r, cb(); return *this; }
    auto &operator-=(const T &r) && { x -= r, cb(); return *this; }
    auto &operator*=(const T &r) && { x *= r, cb(); return *this; }
    auto &operator/=(const T &r) && { x /= r, cb(); return *this; }
    auto &operator%=(const T &r) && { x %= r, cb(); return *this; }
    auto &operator=(const T &r) && { x = r, cb(); return *this; }
    auto &operator<<=(const T &r) && { x <<= r, cb(); return *this; }
    auto &operator>>=(const T &r) && { x >>= r, cb(); return *this; }
    template<class F> auto &apply(F &&f) && { x = f(x), cb(); return *this; }
};
// clang-format on
