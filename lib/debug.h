#include "bits/stdc++.h"
using namespace std;

#define ty typename
#define to_str to_string

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;


#pragma GCC diagnostic ignored "-Wc++17-extensions"

#ifdef __SIZEOF_INT128__
using i128 = __int128_t;
using u128 = __uint128_t;
str to_str(i128 x) {
    str s = "";
    if (x < 0) s += "-", x = -x;
    if (x > 9) s += to_str(x / 10);
    s.push_back(char(x % 10) + '0');
    return s;
}
str to_str(u128 x) {
    str s = "";
    if (x > 9) s += to_str(x / 10);
    s.push_back(char(x % 10) + '0');
    return s;
}
#endif
str to_str(bool b) { return b ? "true" : "false"; }
str to_str(char c) { return "'" + str(1, c) + "'"; }
str to_str(const str &s) { return '"' + s + '"'; }
template<size_t N> str to_str(const bitset<N> &b) { return b.to_string(); }

template<ty T, ty U> str to_str(const pair<T, U>&);
template<ty T> str to_str(const vector<T>&);
template<ty T, size_t N> str to_str(const array<T, N>&);
template<ty T> str to_str(const T&);

template<size_t i = 0, class... Ts> string tup_str_helper(const tuple<Ts...> &t) {
    if constexpr (i == sizeof...(Ts)) { return ""; }
    else return (i ? ", " : "") + to_string(get<i>(t)) + tup_str_helper<i + 1>(t);
}
template<class... Ts> str to_str(const tuple<Ts...> &tup) {
    return "(" + tup_str_helper(tup) + ")";
}

template<ty T, ty U> str to_str(const pair<T, U> &p) {
    return "(" + to_str(p.first) + ", " + to_str(p.second) + ")";
}
template<ty T> str to_str(const vector<T> &v) {
    i32 f = 0;
    str s = "[";
    for (const auto &i : v) s += (f++ ? ", " : "") + to_str(i);
    s += "]";
    return s;
}
template<ty T, size_t N> str to_str(const array<T, N> &arr) {
    i32 f = 0;
    str s = "[";
    for (const auto &i : arr) s += (f++ ? ", " : "") + to_str(i);
    s += "]";
    return s;
}
template<ty T> str to_str(const T &x) {
    i32 f = 0;
    str s = "{";
    for (const auto &i : x) s += (f++ ? ", " : "") + to_str(i);
    s += "}";
    return s;
}


inline str _fmt() { return ""; }
template<ty T, ty... U> str _fmt(T &&t, U &&...u) {
    return to_str(t) + (sizeof...(u) ? ", " : "") + _fmt(u...);
}

template<class T>
void _print(const str &vars, int line, const T &x) {
    cerr << "[\e[33mDEBUG\e[0m:" << line << "] ";
    cerr << vars << " = " << to_str(x) << "\n";
}
template<class... Args, enable_if_t<sizeof...(Args) != 1, int> = 1>
void _print(const str &vars, int line, Args &&...args) {
    cerr << "[\e[33mDEBUG\e[0m:" << line << "] ";
    cerr << "[" << vars << "]";
    cerr << " = ";
    cerr << "[" << _fmt(args...) << "]\n";
}

#define dbg(a...) _print(#a, __LINE__, a)

#undef ty
#undef to_str

#pragma GCC diagnostic warning "-Wc++17-extensions"
