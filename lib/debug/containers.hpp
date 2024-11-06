#pragma once

#include "info_fwd.hpp"
#include "type_check.hpp"

namespace dbg {
    using namespace std;

    extern int indent_lvl;
    extern string get_indent();

    namespace _detail {
        template<typename T>
        inline string dbg_iterable(T &&a, string open, string close) {
            indent_lvl++;
            const bool trivial_value =
                _detail::is_trivial_v<decltype(*a.begin())>;
            const string sep = trivial_value ? ", " : ",\n" + get_indent();

            vector<string> vals;
            for (auto &elem : a) vals.push_back(dbg_info(elem));

            string output = open + (trivial_value ? "" : "\n" + get_indent());
            bool first_elem = true;
            for (string &val : vals) {
                if (first_elem) {
                    output += val;
                    first_elem = false;
                } else {
                    output += sep + val;
                }
            }
            indent_lvl--;
            output += (trivial_value ? "" : "\n" + get_indent()) + close;
            return output;
        }

        template<typename T> inline string dbg_map(T &&mp) {
            indent_lvl++;
            const string sep = "\n" + get_indent();
            vector<string> vals;
            for (auto &[key, val] : mp)
                vals.push_back(dbg_info(key) + " -> " + dbg_info(val));

            string output = "{\n" + get_indent();
            bool first_elem = true;
            for (string &val : vals) {
                if (first_elem) {
                    output += val;
                    first_elem = false;
                } else {
                    output += sep + val;
                }
            }
            indent_lvl--;
            output += "\n" + get_indent() + "}";
            return output;
        }

        template<typename T>
        inline string dbg_stack(T st) { // works with priority_queue too
            vector<typename T::value_type> v;
            while (!st.empty()) v.push_back(st.top()), st.pop();
            return dbg_iterable(v, "{", "}");
        }
        template<typename T, typename... Args>
        inline string dbg_queue(queue<T, Args...> q) {
            vector<T> v;
            while (!q.empty()) v.push_back(q.front()), q.pop();
            return dbg_iterable(v, "{", "}");
        }
    } // namespace _detail
} // namespace dbg
