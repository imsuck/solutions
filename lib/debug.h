#include "bits/stdc++.h"
using namespace std;

#define ty typename
#define to_str to_string

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;

#ifdef __SIZEOF_INT128__
using i128 = __int128_t;
using u128 = __uint128_t;
str to_str(i128 x) {
    str s = "";
    if (x < 0)
        s += "-", x = -x;
    if (x > 9)
        s += to_str(x / 10);
    s.push_back(char(x % 10) + '0');
    return s;
}
str to_str(u128 x) {
    str s = "";
    if (x > 9)
        s += to_str(x / 10);
    s.push_back(char(x % 10) + '0');
    return s;
}
#endif
str to_str(bool b) { return b ? "true" : "false"; }
str to_str(char c) { return "'" + str(1, c) + "'"; }
str to_str(const str &s) { return '"' + s + '"'; }

template <ty T, ty U> str to_str(const pair<T, U> &p) {
    return "(" + to_str(p.first) + ", " + to_str(p.second) + ")";
}
template <ty T, ty U, ty V> str to_str(const tuple<T, U, V> &t) {
    return "(" + to_str(get<0>(t)) + ", " + to_str(get<1>(t)) + ", " +
           to_str(get<2>(t)) + ")";
}
template <ty T, ty U, ty V, ty W> str to_str(const tuple<T, U, V, W> &t) {
    return "(" + to_str(get<0>(t)) + ", " + to_str(get<1>(t)) + ", " +
           to_str(get<2>(t)) + ", " + to_str(get<3>(t)) + ")";
}

template <ty T> str to_str(const vector<T> &x) {
    i32 f = 0;
    str s = "[";
    for (const auto &i : x)
        s += (f++ ? ", " : "") + to_str(i);
    s += "]";
    return s;
}
template <ty T> str to_str(T x[]) {
    i32 f = 0;
    str s = "[";
    for (auto it = begin(x); it != end(x); it++)
        s += (f++ ? ", " : "") + to_str(*it);
    s += "]";
    return s;
}
template <ty T> str to_str(const T &x) {
    i32 f = 0;
    str s = "{";
    for (const auto &i : x)
        s += (f++ ? ", " : "") + to_str(i);
    s += "}";
    return s;
}
template <size_t N> str to_str(const bitset<N> &b) {
    str s = "";
    for (size_t i = N - 1; i > 0; i--)
        s += b[i] + '0';
    s += b[0] + '0';
    return s;
}

str _fmt() { return ""; }
template <ty T, ty... U> str _fmt(const T &t, const U &...u) {
    return to_str(t) + (sizeof...(u) ? ", " : "") + _fmt(u...);
}

#define dbg_1(a)                                                               \
    cerr << "[\e[33mDEBUG\e[0m:" << __LINE__ << "] " << #a << " = "            \
         << to_str(a) << "\n"
#define dbg_mul(a...)                                                          \
    cerr << "[\e[33mDEBUG\e[0m:" << __LINE__ << "] "                           \
         << "[" << #a << "] = [" << _fmt(a) << "]\n"
#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define dbg(...)                                                               \
    GET_MACRO(__VA_ARGS__, dbg_mul, dbg_mul, dbg_mul, dbg_mul, dbg_mul,        \
              dbg_mul, dbg_mul, dbg_1)                                         \
    (__VA_ARGS__)

#undef ty
#undef to_strt
