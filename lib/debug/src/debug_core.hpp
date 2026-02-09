#pragma once

#include <iostream>
#include <string>
#include <utility>

#include "colors.hpp"
#include "formatter.hpp"

// Helper macro to get function name
#define DBG_FUNCTION_NAME __func__

// Helper macro to get current line
#define DBG_LINE __LINE__

// Helper macro to stringify
#define DBG_STRINGIFY(x) #x
#define DBG_TOSTRING(x) DBG_STRINGIFY(x)

namespace dbg {
    namespace detail {
        template<typename T>
        std::string format_arg(const char *name, const T &value) {
            std::string result = with_color(name, Color::Blue);
            result += with_color(" = ", Color::BrightBlack);
            result += format_value(value);
            return result;
        }

        template<typename... Args, size_t... Is>
        std::string format_args_impl(
            const std::tuple<Args...> &args_tuple,
            const std::array<const char *, sizeof...(Args)> &names,
            std::index_sequence<Is...>
        ) {
            std::string arg_str = with_color("[", Color::BrightBlack);
            ((arg_str += (Is == 0 ? "" : with_color(", ", Color::BrightBlack)) +
                         with_color(names[Is], Color::Blue)),
             ...);
            arg_str += with_color("] = [", Color::BrightBlack);

            ((arg_str += (Is == 0 ? "" : with_color(", ", Color::BrightBlack)) +
                         format_value(std::get<Is>(args_tuple))),
             ...);
            arg_str += with_color("]", Color::BrightBlack);

            return arg_str;
        }

        template<typename... Args>
        std::string format_container_like(
            const std::array<const char *, sizeof...(Args)> &names,
            const Args &...args
        ) {
            std::string result = with_color("[", Color::BrightBlack);
            bool first = true;

            IndentGuard guard;

            // Format each argument on a new line since we have non-trivial args
            size_t idx = 0;
            ((result +=
              (first ? "\n" + indent_str(1)
                     : with_color(",\n", Color::BrightBlack) + indent_str(1)) +
              with_color(names[idx], Color::Blue) +
              with_color(" = ", Color::BrightBlack) + format_value(args),
              first = false,
              ++idx),
             ...);

            result += "\n" + with_color("]", Color::BrightBlack);
            return result;
        }

        template<typename... Args>
        std::string format_multiple_args(
            const std::array<const char *, sizeof...(Args)> &names,
            const Args &...args
        ) {
            bool has_non_trivial = (!::dbg::is_trivial_v(args) || ...);

            if (has_non_trivial) {
                return format_container_like(names, args...);
            } else {
                return format_args_impl(
                    std::forward_as_tuple(args...),
                    names,
                    std::make_index_sequence<sizeof...(Args)>{}
                );
            }
        }

        inline void debug_output(
            const char *func_name,
            int line,
            const std::string &content
        ) {
            std::cerr << with_color("[", Color::BrightBlack)
                      << with_color(func_name, Color::Yellow)

                      << with_color(":", Color::BrightBlack) << line
                      << with_color("] ", Color::BrightBlack) << content
                      << std::endl;
        }

    } // namespace detail

    template<typename T>
    void
    dbg(const char *func_name, int line, const char *name, const T &value) {
        detail::debug_output(func_name, line, detail::format_arg(name, value));
    }

    template<typename... Args>
    void
    dbg(const char *func_name,
        int line,
        const std::array<const char *, sizeof...(Args)> &names,
        const Args &...args) {
        detail::debug_output(
            func_name,
            line,
            detail::format_multiple_args(names, args...)
        );
    }
} // namespace dbg

// Helper macros for argument counting
#define DBG_COUNT_ARGS(...)                                                    \
    DBG_COUNT_ARGS_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define DBG_COUNT_ARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) _11

#define DBG_CONCAT(a, b) a##b
#define DBG_MAKE_NAME(prefix, line) DBG_CONCAT(prefix, line)

#define DBG_CHOOSE_MACRO(count, ...) DBG_CONCAT(DBG_DEBUG_, count)(__VA_ARGS__)

#define DBG_DEBUG_1(expr)                                                      \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val_, __LINE__) = (expr);                    \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            #expr,                                                             \
            DBG_MAKE_NAME(_dbg_val_, __LINE__)                                 \
        );                                                                     \
    }()))

#define DBG_DEBUG_2(expr1, expr2)                                              \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        std::array<const char *, 2> DBG_MAKE_NAME(_dbg_names_, __LINE__) = {   \
            #expr1,                                                            \
            #expr2                                                             \
        };                                                                     \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_3(expr1, expr2, expr3)                                       \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        std::array<const char *, 3> DBG_MAKE_NAME(                             \
            _dbg_names_,                                                       \
            __LINE__                                                           \
        ) = {#expr1, #expr2, #expr3};                                          \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_4(expr1, expr2, expr3, expr4)                                \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        auto &&DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4);                  \
        std::array<const char *, 4> DBG_MAKE_NAME(                             \
            _dbg_names_,                                                       \
            __LINE__                                                           \
        ) = {#expr1, #expr2, #expr3, #expr4};                                  \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val4_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_5(expr1, expr2, expr3, expr4, expr5)                         \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        auto &&DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4);                  \
        auto &&DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5);                  \
        std::array<const char *, 5> DBG_MAKE_NAME(                             \
            _dbg_names_,                                                       \
            __LINE__                                                           \
        ) = {#expr1, #expr2, #expr3, #expr4, #expr5};                          \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val4_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val5_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_6(expr1, expr2, expr3, expr4, expr5, expr6)                  \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        auto &&DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4);                  \
        auto &&DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5);                  \
        auto &&DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6);                  \
        std::array<const char *, 6> DBG_MAKE_NAME(                             \
            _dbg_names_,                                                       \
            __LINE__                                                           \
        ) = {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6};                  \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val4_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val5_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val6_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_7(expr1, expr2, expr3, expr4, expr5, expr6, expr7)           \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        auto &&DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4);                  \
        auto &&DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5);                  \
        auto &&DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6);                  \
        auto &&DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7);                  \
        std::array<const char *, 7> DBG_MAKE_NAME(                             \
            _dbg_names_,                                                       \
            __LINE__                                                           \
        ) = {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6, #expr7};          \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val4_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val5_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val6_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val7_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_8(expr1, expr2, expr3, expr4, expr5, expr6, expr7, expr8)    \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        auto &&DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4);                  \
        auto &&DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5);                  \
        auto &&DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6);                  \
        auto &&DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7);                  \
        auto &&DBG_MAKE_NAME(_dbg_val8_, __LINE__) = (expr8);                  \
        std::array<const char *, 8> DBG_MAKE_NAME(                             \
            _dbg_names_,                                                       \
            __LINE__                                                           \
        ) = {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6, #expr7, #expr8};  \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val4_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val5_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val6_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val7_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val8_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_9(                                                           \
    expr1,                                                                     \
    expr2,                                                                     \
    expr3,                                                                     \
    expr4,                                                                     \
    expr5,                                                                     \
    expr6,                                                                     \
    expr7,                                                                     \
    expr8,                                                                     \
    expr9                                                                      \
)                                                                              \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        auto &&DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4);                  \
        auto &&DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5);                  \
        auto &&DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6);                  \
        auto &&DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7);                  \
        auto &&DBG_MAKE_NAME(_dbg_val8_, __LINE__) = (expr8);                  \
        auto &&DBG_MAKE_NAME(_dbg_val9_, __LINE__) = (expr9);                  \
        std::array<const char *, 9> DBG_MAKE_NAME(_dbg_names_, __LINE__) = {   \
            #expr1,                                                            \
            #expr2,                                                            \
            #expr3,                                                            \
            #expr4,                                                            \
            #expr5,                                                            \
            #expr6,                                                            \
            #expr7,                                                            \
            #expr8,                                                            \
            #expr9                                                             \
        };                                                                     \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val4_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val5_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val6_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val7_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val8_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val9_, __LINE__)                                \
        );                                                                     \
    }()))

#define DBG_DEBUG_10(                                                          \
    expr1,                                                                     \
    expr2,                                                                     \
    expr3,                                                                     \
    expr4,                                                                     \
    expr5,                                                                     \
    expr6,                                                                     \
    expr7,                                                                     \
    expr8,                                                                     \
    expr9,                                                                     \
    expr10                                                                     \
)                                                                              \
    ((void)([&]() {                                                            \
        auto &&DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1);                  \
        auto &&DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2);                  \
        auto &&DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3);                  \
        auto &&DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4);                  \
        auto &&DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5);                  \
        auto &&DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6);                  \
        auto &&DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7);                  \
        auto &&DBG_MAKE_NAME(_dbg_val8_, __LINE__) = (expr8);                  \
        auto &&DBG_MAKE_NAME(_dbg_val9_, __LINE__) = (expr9);                  \
        auto &&DBG_MAKE_NAME(_dbg_val10_, __LINE__) = (expr10);                \
        std::array<const char *, 10> DBG_MAKE_NAME(_dbg_names_, __LINE__) = {  \
            #expr1,                                                            \
            #expr2,                                                            \
            #expr3,                                                            \
            #expr4,                                                            \
            #expr5,                                                            \
            #expr6,                                                            \
            #expr7,                                                            \
            #expr8,                                                            \
            #expr9,                                                            \
            #expr10                                                            \
        };                                                                     \
        ::dbg::dbg(                                                            \
            DBG_FUNCTION_NAME,                                                 \
            __LINE__,                                                          \
            DBG_MAKE_NAME(_dbg_names_, __LINE__),                              \
            DBG_MAKE_NAME(_dbg_val1_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val2_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val3_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val4_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val5_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val6_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val7_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val8_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val9_, __LINE__),                               \
            DBG_MAKE_NAME(_dbg_val10_, __LINE__)                               \
        );                                                                     \
    }()))

// Macros for custom struct formatting (up to 10 fields)
#define DBG_FORMAT_STRUCT1(Type, field1, ...)                                  \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT2(Type, field1, field2, ...)                          \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT3(Type, field1, field2, field3, ...)                  \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT4(Type, field1, field2, field3, field4, ...)          \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT5(Type, field1, field2, field3, field4, field5, ...)  \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field5, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field5)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT6(                                                    \
    Type,                                                                      \
    field1,                                                                    \
    field2,                                                                    \
    field3,                                                                    \
    field4,                                                                    \
    field5,                                                                    \
    field6,                                                                    \
    ...                                                                        \
)                                                                              \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field5, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field5)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field6, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field6)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT7(                                                    \
    Type,                                                                      \
    field1,                                                                    \
    field2,                                                                    \
    field3,                                                                    \
    field4,                                                                    \
    field5,                                                                    \
    field6,                                                                    \
    field7,                                                                    \
    ...                                                                        \
)                                                                              \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field5, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field5)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field6, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field6)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field7, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field7)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT8(                                                    \
    Type,                                                                      \
    field1,                                                                    \
    field2,                                                                    \
    field3,                                                                    \
    field4,                                                                    \
    field5,                                                                    \
    field6,                                                                    \
    field7,                                                                    \
    field8,                                                                    \
    ...                                                                        \
)                                                                              \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field5, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field5)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field6, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field6)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field7, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field7)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field8, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field8)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT9(                                                    \
    Type,                                                                      \
    field1,                                                                    \
    field2,                                                                    \
    field3,                                                                    \
    field4,                                                                    \
    field5,                                                                    \
    field6,                                                                    \
    field7,                                                                    \
    field8,                                                                    \
    field9,                                                                    \
    ...                                                                        \
)                                                                              \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field5, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field5)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field6, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field6)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field7, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field7)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field8, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field8)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field9, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field9)                      \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

#define DBG_FORMAT_STRUCT10(                                                   \
    Type,                                                                      \
    field1,                                                                    \
    field2,                                                                    \
    field3,                                                                    \
    field4,                                                                    \
    field5,                                                                    \
    field6,                                                                    \
    field7,                                                                    \
    field8,                                                                    \
    field9,                                                                    \
    field10,                                                                   \
    ...                                                                        \
)                                                                              \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        return os                                                              \
               << #Type                                                        \
               << ::dbg::detail::with_color(" { ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field5, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field5)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field6, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field6)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field7, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field7)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field8, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field8)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field9, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field9)                      \
               << ::dbg::detail::with_color(", ", ::dbg::Color::BrightBlack)   \
               << ::dbg::detail::with_color(#field10, ::dbg::Color::Cyan)      \
               << ::dbg::detail::with_color("=", ::dbg::Color::BrightBlack)    \
               << ::dbg::detail::format_value(obj.field10)                     \
               << ::dbg::detail::with_color(" }", ::dbg::Color::BrightBlack);  \
    }

// Automatic dispatch macro using buffer arguments
#define DBG_FORMAT_STRUCT(Type, ...)                                           \
    DBG_FORMAT_STRUCT_DISPATCH(                                                \
        Type,                                                                  \
        __VA_ARGS__,                                                           \
        10,                                                                    \
        9,                                                                     \
        8,                                                                     \
        7,                                                                     \
        6,                                                                     \
        5,                                                                     \
        4,                                                                     \
        3,                                                                     \
        2,                                                                     \
        1,                                                                     \
        0                                                                      \
    )

#define DBG_FORMAT_STRUCT_DISPATCH(                                            \
    Type,                                                                      \
    _1,                                                                        \
    _2,                                                                        \
    _3,                                                                        \
    _4,                                                                        \
    _5,                                                                        \
    _6,                                                                        \
    _7,                                                                        \
    _8,                                                                        \
    _9,                                                                        \
    _10,                                                                       \
    N,                                                                         \
    ...                                                                        \
)                                                                              \
    DBG_FORMAT_STRUCT##N(                                                      \
        Type,                                                                  \
        _1,                                                                    \
        _2,                                                                    \
        _3,                                                                    \
        _4,                                                                    \
        _5,                                                                    \
        _6,                                                                    \
        _7,                                                                    \
        _8,                                                                    \
        _9,                                                                    \
        _10,                                                                   \
        __VA_ARGS__                                                            \
    )

// Pretty print struct formatting (multiline)
#define DBG_PRETTY_STRUCT1(Type, field1, ...)                                  \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field1) << "\n";             \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT2(Type, field1, field2, ...)                          \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field2) << "\n";             \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT3(Type, field1, field2, field3, ...)                  \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field3) << "\n";             \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT4(Type, field1, field2, field3, field4, ...)          \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field4) << "\n";             \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT5(Type, field1, field2, field3, field4, field5, ...)  \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field1, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field1)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field2, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field2)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field3, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field3)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field4, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field4)                      \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#field5, ::dbg::Color::Cyan)       \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.field5) << "\n";             \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT6(Type, f1, f2, f3, f4, f5, f6, ...)                  \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f1, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f1)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f2, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f2)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f3, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f3)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f4, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f4)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f5, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f5)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f6, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f6) << "\n";                 \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT7(Type, f1, f2, f3, f4, f5, f6, f7, ...)              \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f1, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f1)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f2, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f2)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f3, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f3)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f4, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f4)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f5, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f5)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f6, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f6)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f7, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f7) << "\n";                 \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT8(Type, f1, f2, f3, f4, f5, f6, f7, f8, ...)          \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f1, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f1)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f2, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f2)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f3, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f3)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f4, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f4)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f5, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f5)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f6, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f6)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f7, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f7)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f8, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f8) << "\n";                 \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT9(Type, f1, f2, f3, f4, f5, f6, f7, f8, f9, ...)      \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f1, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f1)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f2, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f2)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f3, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f3)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f4, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f4)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f5, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f5)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f6, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f6)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f7, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f7)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f8, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f8)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f9, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f9) << "\n";                 \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT10(                                                   \
    Type,                                                                      \
    f1,                                                                        \
    f2,                                                                        \
    f3,                                                                        \
    f4,                                                                        \
    f5,                                                                        \
    f6,                                                                        \
    f7,                                                                        \
    f8,                                                                        \
    f9,                                                                        \
    f10,                                                                       \
    ...                                                                        \
)                                                                              \
    inline std::ostream &operator<<(std::ostream &os, const Type &obj) {       \
        os << #Type                                                            \
           << ::dbg::detail::with_color(" {\n", ::dbg::Color::BrightBlack);    \
        {                                                                      \
            ::dbg::IndentGuard guard;                                          \
            os << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f1, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f1)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f2, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f2)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f3, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f3)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f4, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f4)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f5, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f5)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f6, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f6)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f7, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f7)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f8, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f8)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f9, ::dbg::Color::Cyan)           \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f9)                          \
               << ::dbg::detail::with_color(",\n", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color(#f10, ::dbg::Color::Cyan)          \
               << ::dbg::detail::with_color(" = ", ::dbg::Color::BrightBlack)  \
               << ::dbg::detail::format_value(obj.f10) << "\n";                \
        }                                                                      \
        return os                                                              \
               << ::dbg::detail::indent_str(                                   \
                      ::dbg::IndentGuard::get_current_level()                  \
                  )                                                            \
               << ::dbg::detail::with_color("}", ::dbg::Color::BrightBlack);   \
    }

#define DBG_PRETTY_STRUCT(Type, ...)                                           \
    DBG_PRETTY_STRUCT_DISPATCH(                                                \
        Type,                                                                  \
        __VA_ARGS__,                                                           \
        10,                                                                    \
        9,                                                                     \
        8,                                                                     \
        7,                                                                     \
        6,                                                                     \
        5,                                                                     \
        4,                                                                     \
        3,                                                                     \
        2,                                                                     \
        1,                                                                     \
        0                                                                      \
    )

#define DBG_PRETTY_STRUCT_DISPATCH(                                            \
    Type,                                                                      \
    _1,                                                                        \
    _2,                                                                        \
    _3,                                                                        \
    _4,                                                                        \
    _5,                                                                        \
    _6,                                                                        \
    _7,                                                                        \
    _8,                                                                        \
    _9,                                                                        \
    _10,                                                                       \
    N,                                                                         \
    ...                                                                        \
)                                                                              \
    DBG_PRETTY_STRUCT##N(                                                      \
        Type,                                                                  \
        _1,                                                                    \
        _2,                                                                    \
        _3,                                                                    \
        _4,                                                                    \
        _5,                                                                    \
        _6,                                                                    \
        _7,                                                                    \
        _8,                                                                    \
        _9,                                                                    \
        _10,                                                                   \
        __VA_ARGS__                                                            \
    )

// Or use the direct macros: DBG_FORMAT_STRUCT1 through DBG_FORMAT_STRUCT10
