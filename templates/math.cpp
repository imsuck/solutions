#include <cstdint>

namespace utils {
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    u64 lo(u64 x) { return u32(x); }
    u64 hi(u64 x) { return x >> 32; }
    // Gets the high bits of 64-bit int multiplication
    u64 mulhi(u64 a, u64 b) {
#ifdef __SIZEOF_INT128__
        return ((__uint128_t)a * b) >> 64;
#else
        u64 h = hi(a) * hi(b);
        u64 m1 = lo(a) * hi(b), m2 = hi(a) * lo(b);
        u64 l = lo(a) * lo(b);

        u64 c = hi(lo(m1) + lo(m2) + hi(l));

        return h + hi(m1) + hi(m2) + c;
#endif
    }
} // namespace utils

using utils::mulhi;
