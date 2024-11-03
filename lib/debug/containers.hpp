#pragma once
#include <array>
#include <sstream>
#include <vector>
using namespace std;

template<ty T> str to_str(const vector<T> &);
template<ty T, size_t N> str to_str(const array<T, N> &);
template<ty T, enable_if_t<dbg_internal::streamable_v<T>, int>>
str to_str(T &&);
template<ty T, enable_if_t<dbg_internal::iterable_v<T>, int>> str to_str(T &&);

template<ty T> str to_str(const vector<T> &v) {
    constexpr bool trivial_val = dbg_internal::_trivial<T>;
    i32 f = 0;
    str s;
    {
        dbg::inc_indent _indt(!trivial_val);
        s = (trivial_val ? "[" : "[\n" + dbg::get_indent());
        for (auto &&i : v) {
            if (f++) {
                if constexpr (trivial_val) s += ", ";
                else s += ",\n" + dbg::get_indent();
            }
            s += to_str(i);
        }
    }
    s += (trivial_val ? "]" : "\n" + dbg::get_indent() + "]");
    return s;
}
template<ty T, size_t N> str to_str(const array<T, N> &arr) {
    constexpr bool trivial_val = dbg_internal::_trivial<T>;
    i32 f = 0;
    str s;
    {
        dbg::inc_indent _indt(!trivial_val);
        s = (trivial_val ? "[" : "[\n" + dbg::get_indent());
        for (auto &&i : arr) {
            if (f++) {
                if constexpr (trivial_val) s += ", ";
                else s += ",\n" + dbg::get_indent();
            }
            s += to_str(i);
        }
    }
    s += (trivial_val ? "]" : "\n" + dbg::get_indent() + "]");
    return s;
}
template<ty T, enable_if_t<dbg_internal::streamable_v<T> &&
                               !is_same_v<decay_t<T>, basic_string<char>>,
                           int> = 1>
str to_str(T &&x) {
    stringstream ss;
    ss << x;
    return ss.str();
}
template<ty T, ty _T = decay_t<T>,
         enable_if_t<dbg_internal::iterable_v<_T> &&
                         !dbg_internal::is_vector_v<_T> &&
                         !is_same_v<_T, basic_string<char>>,
                     int> = 1>
str to_str(T &&x) {
    constexpr bool trivial_val = dbg_internal::_trivial<decltype(*x.begin())>;
    i32 f = 0;
    str s;
    {
        dbg::inc_indent _indt(!trivial_val);
        s = (trivial_val ? "{" : "{\n" + dbg::get_indent());
        for (auto &&i : x) {
            if (f++) {
                if constexpr (trivial_val) s += ", ";
                else s += ",\n" + dbg::get_indent();
            }
            s += to_str(i);
        }
    }
    s += (trivial_val ? "}" : "\n" + dbg::get_indent() + "}");
    return s;
}
