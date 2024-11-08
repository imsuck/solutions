#ifndef LOCAL
    #define dbg(...) void()
    #define mark_dbg() if (false)
#else
namespace dbg::options {
    template<> constexpr bool trivial_string() { return false; }
} // namespace dbg::options
#endif
