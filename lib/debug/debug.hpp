#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

#define ty typename
#define to_str to_string

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;

namespace dbg {
    static int indent_lvl = 0;
    str get_indent() { return str(2 * indent_lvl, ' '); }
    struct inc_indent {
        bool on;
        inc_indent(bool b) : on(b) { indent_lvl += on; }
        ~inc_indent() { indent_lvl -= on; }
    };
} // namespace dbg

#include "macros.hpp"
#include "type_check.hpp"

#include "forward_decl.hpp"

#include "containers.hpp"
#include "trivial.hpp"

namespace dbg {
    inline str _fmt() { return ""; }
    template<ty T, ty... U> str _fmt(T &&t, U &&...u) {
        return to_str(t) + (sizeof...(u) ? ", " : "") + _fmt(u...);
    }

    template<ty T>
    void _print(const str &func, const str &vars, int line, T &&x) {
        cerr << "[\e[33m" << func << "\e[0m:" << line << "] ";
        cerr << vars << " = " << to_str(x) << "\n";
    }
    template<ty... Args>
    enable_if_t<sizeof...(Args) != 1> _print(const str &func, const str &vars,
                                             int line, Args &&...args) {
        cerr << "[\e[33m" << func << "\e[0m:" << line << "] ";
        cerr << "[" << vars << "]";
        cerr << " = ";
        cerr << "[" << _fmt(args...) << "]\n";
    }
}

#define dbg(a...) dbg::_print(__func__, #a, __LINE__, a)
#define mark_dbg()

#undef ty
#undef to_str
