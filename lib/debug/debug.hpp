#pragma once

#include <iostream>
#include <string>

namespace dbg {
    using namespace std;

    inline int indent_lvl = 0;
    inline string get_indent() { return string(2 * indent_lvl, ' '); }
} // namespace dbg

#include "info.hpp"

namespace dbg {
    namespace _detail {
        struct src_loc {
            string file_name;
            int line;
            string func_name;
        };

        template<typename...> string fmt() { return ""; }
        template<typename T, typename... Args>
        string fmt(T &&x, Args &&...args) {
            return dbg_info(x) + (sizeof...(args) ? ", " + fmt(args...) : "");
        }
    }; // namespace _detail

    template<typename... Args>
    void dbg_impl(_detail::src_loc loc, string args_str, Args &&...args) {
        const bool multi_arg = sizeof...(args) > 1;
        const string label =
            "[\e[33m" + loc.func_name + "\e[0m:" + to_string(loc.line) + "]";

        string vals = _detail::fmt(args...);

        if (multi_arg) {
            args_str = "[" + args_str + "]";
            vals = "[" + vals + "]";
        }

        const string output = label + " " + args_str + " = " + vals;
        cerr << output << "\n";
    }
} // namespace dbg

#define dbg(a...) dbg::dbg_impl({__FILE__, __LINE__, __func__}, #a, a)
#define mark_dbg()
