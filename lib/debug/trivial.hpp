#pragma once
#include <bitset>
using namespace std;

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

// tuples, pairs
template<size_t i = 0, ty... Ts>
string tup_str_helper(const tuple<Ts...> &t) {
    if constexpr (i == sizeof...(Ts)) return "";
    else return (i ? ", " : "") + to_string(get<i>(t)) +
               tup_str_helper<i + 1>(t);
}
template<ty... Ts> str to_str(const tuple<Ts...> &tup) {
    return "(" + tup_str_helper(tup) + ")";
}
template<ty T, ty U> str to_str(const pair<T, U> &p) {
    return "(" + to_str(p.first) + ", " + to_str(p.second) + ")";
}
