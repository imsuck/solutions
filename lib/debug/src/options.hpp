#pragma once

#include <cstddef>

namespace dbg::options {
    inline bool fixed_float = false;
    inline int float_precision = 6;
    inline bool trivial_string = true;
    inline bool enable_colors = true;
    inline int max_container_elements = 20;
    inline bool show_multiplicity = true;
} // namespace dbg::options

namespace dbg {
    class IndentGuard {
      public:
        IndentGuard() { ++get_indent_level(); }

        ~IndentGuard() { --get_indent_level(); }

        IndentGuard(const IndentGuard &) = delete;
        IndentGuard &operator=(const IndentGuard &) = delete;

        static int get_current_level() { return get_indent_level(); }

      private:
        static int &get_indent_level() {
            static thread_local int indent_level = 0;
            return indent_level;
        }
    };
} // namespace dbg
