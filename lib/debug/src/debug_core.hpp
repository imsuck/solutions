#pragma once

#include "colors.hpp"
#include "formatter.hpp"
#include "options.hpp"
#include <iostream>
#include <string>
#include <utility>

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
            std::string result = name;
            result += " = ";
            result += format_value(value);
            return result;
        }

        template<typename... Args, size_t... Is>
        std::string format_args_impl(
            const std::tuple<Args...> &args_tuple,
            const std::array<const char *, sizeof...(Args)> &names,
            std::index_sequence<Is...>
        ) {
            std::string arg_str = "[";
            ((arg_str += (Is == 0 ? "" : ", ") + std::string(names[Is])), ...);
            arg_str += "] = [";

            ((arg_str +=
              (Is == 0 ? "" : ", ") + format_value(std::get<Is>(args_tuple))),
             ...);
            arg_str += "]";

            return arg_str;
        }

        template<typename... Args>
        std::string format_container_like(
            const std::array<const char *, sizeof...(Args)> &names,
            const Args &...args
        ) {
            std::string result = "[";
            bool first = true;

            IndentGuard guard;

            // Format each argument on a new line since we have non-trivial args
            size_t idx = 0;
            ((result += (first ? "\n" + indent_str(1) : ",\n" + indent_str(1)) +
                        std::string(names[idx]) + " = " + format_value(args, 1),
              first = false,
              ++idx),
             ...);

            result += "\n]";
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
            std::cerr << "["
                      << (options::enable_colors ? Color::Yellow : Color::Reset)
                      << func_name << Color::Reset << ":" << line << "] "
                      << content << std::endl;
        }

    } // namespace detail

    template<typename T>
    void
    dbg(const char *func_name, int line, const char *name, const T &value) {
        detail::debug_output(func_name, line, detail::format_arg(name, value));
    }

    template<typename... Args>
    void dbg(
        const char *func_name,
        int line,
        const std::array<const char *, sizeof...(Args)> &names,
        const Args &...args
    ) {
        detail::debug_output(
            func_name,
            line,
            detail::format_multiple_args(names, args...)
        );
    }
} // namespace dbg

// Helper macros for argument counting
#define DBG_COUNT_ARGS(...) DBG_COUNT_ARGS_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define DBG_COUNT_ARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, ...) _11

#define DBG_CONCAT(a, b) a##b
#define DBG_MAKE_NAME(prefix, line) DBG_CONCAT(prefix, line)

#define DBG_CHOOSE_MACRO(count, ...) DBG_CONCAT(DBG_DEBUG_, count)(__VA_ARGS__)

#define DBG_DEBUG_1(expr) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val_, __LINE__) = (expr); \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, #expr, DBG_MAKE_NAME(_dbg_val_, __LINE__)); \
  }()))

#define DBG_DEBUG_2(expr1, expr2) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    std::array<const char*, 2> DBG_MAKE_NAME(_dbg_names_, __LINE__) = {#expr1, #expr2}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__)); \
  }()))

#define DBG_DEBUG_3(expr1, expr2, expr3) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    std::array<const char*, 3> DBG_MAKE_NAME(_dbg_names_, __LINE__) = {#expr1, #expr2, #expr3}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__)); \
  }()))

#define DBG_DEBUG_4(expr1, expr2, expr3, expr4) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    auto&& DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4); \
    std::array<const char*, 4> DBG_MAKE_NAME(_dbg_names_, __LINE__) = \
        {#expr1, #expr2, #expr3, #expr4}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__), DBG_MAKE_NAME(_dbg_val4_, __LINE__)); \
  }()))

#define DBG_DEBUG_5(expr1, expr2, expr3, expr4, expr5) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    auto&& DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4); \
    auto&& DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5); \
    std::array<const char*, 5> DBG_MAKE_NAME(_dbg_names_, __LINE__) = \
        {#expr1, #expr2, #expr3, #expr4, #expr5}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__), DBG_MAKE_NAME(_dbg_val4_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val5_, __LINE__)); \
  }()))

#define DBG_DEBUG_6(expr1, expr2, expr3, expr4, expr5, expr6) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    auto&& DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4); \
    auto&& DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5); \
    auto&& DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6); \
    std::array<const char*, 6> DBG_MAKE_NAME(_dbg_names_, __LINE__) = \
        {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__), DBG_MAKE_NAME(_dbg_val4_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val5_, __LINE__), DBG_MAKE_NAME(_dbg_val6_, __LINE__)); \
  }()))

#define DBG_DEBUG_7(expr1, expr2, expr3, expr4, expr5, expr6, expr7) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    auto&& DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4); \
    auto&& DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5); \
    auto&& DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6); \
    auto&& DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7); \
    std::array<const char*, 7> DBG_MAKE_NAME(_dbg_names_, __LINE__) = \
        {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6, #expr7}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__), DBG_MAKE_NAME(_dbg_val4_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val5_, __LINE__), DBG_MAKE_NAME(_dbg_val6_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val7_, __LINE__)); \
  }()))

#define DBG_DEBUG_8(expr1, expr2, expr3, expr4, expr5, expr6, expr7, expr8) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    auto&& DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4); \
    auto&& DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5); \
    auto&& DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6); \
    auto&& DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7); \
    auto&& DBG_MAKE_NAME(_dbg_val8_, __LINE__) = (expr8); \
    std::array<const char*, 8> DBG_MAKE_NAME(_dbg_names_, __LINE__) = \
        {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6, #expr7, #expr8}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__), DBG_MAKE_NAME(_dbg_val4_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val5_, __LINE__), DBG_MAKE_NAME(_dbg_val6_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val7_, __LINE__), DBG_MAKE_NAME(_dbg_val8_, __LINE__)); \
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
) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    auto&& DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4); \
    auto&& DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5); \
    auto&& DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6); \
    auto&& DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7); \
    auto&& DBG_MAKE_NAME(_dbg_val8_, __LINE__) = (expr8); \
    auto&& DBG_MAKE_NAME(_dbg_val9_, __LINE__) = (expr9); \
    std::array<const char*, 9> DBG_MAKE_NAME(_dbg_names_, __LINE__) = \
        {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6, #expr7, #expr8, #expr9}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__), DBG_MAKE_NAME(_dbg_val4_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val5_, __LINE__), DBG_MAKE_NAME(_dbg_val6_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val7_, __LINE__), DBG_MAKE_NAME(_dbg_val8_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val9_, __LINE__)); \
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
) \
  ((void)([&]() { \
    auto&& DBG_MAKE_NAME(_dbg_val1_, __LINE__) = (expr1); \
    auto&& DBG_MAKE_NAME(_dbg_val2_, __LINE__) = (expr2); \
    auto&& DBG_MAKE_NAME(_dbg_val3_, __LINE__) = (expr3); \
    auto&& DBG_MAKE_NAME(_dbg_val4_, __LINE__) = (expr4); \
    auto&& DBG_MAKE_NAME(_dbg_val5_, __LINE__) = (expr5); \
    auto&& DBG_MAKE_NAME(_dbg_val6_, __LINE__) = (expr6); \
    auto&& DBG_MAKE_NAME(_dbg_val7_, __LINE__) = (expr7); \
    auto&& DBG_MAKE_NAME(_dbg_val8_, __LINE__) = (expr8); \
    auto&& DBG_MAKE_NAME(_dbg_val9_, __LINE__) = (expr9); \
    auto&& DBG_MAKE_NAME(_dbg_val10_, __LINE__) = (expr10); \
    std::array<const char*, 10> DBG_MAKE_NAME(_dbg_names_, __LINE__) = \
        {#expr1, #expr2, #expr3, #expr4, #expr5, #expr6, #expr7, #expr8, #expr9, #expr10}; \
    ::dbg::dbg(DBG_FUNCTION_NAME, __LINE__, DBG_MAKE_NAME(_dbg_names_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val1_, __LINE__), DBG_MAKE_NAME(_dbg_val2_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val3_, __LINE__), DBG_MAKE_NAME(_dbg_val4_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val5_, __LINE__), DBG_MAKE_NAME(_dbg_val6_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val7_, __LINE__), DBG_MAKE_NAME(_dbg_val8_, __LINE__), \
                 DBG_MAKE_NAME(_dbg_val9_, __LINE__), DBG_MAKE_NAME(_dbg_val10_, __LINE__)); \
  }()))

// Macros for custom struct formatting (up to 10 fields)
#define DBG_FORMAT_STRUCT1(Type, field1, ...)                                                      \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
        return os << #Type "{" #field1 "=" << obj.field1 << "}";                                       \
  }

#define DBG_FORMAT_STRUCT2(Type, field1, field2, ...)                                              \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
        return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) \
                  << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2) << "}";     \
  }

#define DBG_FORMAT_STRUCT3(Type, field1, field2, field3, ...)                                      \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
        return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1)                  \
                  << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)                       \
                  << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << "}";                                            \
  }

#define DBG_FORMAT_STRUCT4(Type, field1, field2, field3, field4, ...)                              \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
    return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)             \
              << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << ", " #field4 "=" << ::dbg::detail::format_value(obj.field4) << "}";          \
  }

#define DBG_FORMAT_STRUCT5(Type, field1, field2, field3, field4, field5, ...)                      \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
    return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)             \
              << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << ", " #field4 "=" << ::dbg::detail::format_value(obj.field4)                  \
              << ", " #field5 "=" << ::dbg::detail::format_value(obj.field5) << "}";                                            \
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
)              \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
    return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)             \
              << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << ", " #field4 "=" << ::dbg::detail::format_value(obj.field4)                  \
              << ", " #field5 "=" << ::dbg::detail::format_value(obj.field5) << ", " #field6 "=" << ::dbg::detail::format_value(obj.field6) << "}";          \
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
)      \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
    return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)             \
              << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << ", " #field4 "=" << ::dbg::detail::format_value(obj.field4)                  \
              << ", " #field5 "=" << ::dbg::detail::format_value(obj.field5) << ", " #field6 "=" << ::dbg::detail::format_value(obj.field6)                  \
              << ", " #field7 "=" << ::dbg::detail::format_value(obj.field7) << "}";                                            \
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
)                                                                    \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
    return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)             \
              << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << ", " #field4 "=" << ::dbg::detail::format_value(obj.field4)                  \
              << ", " #field5 "=" << ::dbg::detail::format_value(obj.field5) << ", " #field6 "=" << ::dbg::detail::format_value(obj.field6)                  \
              << ", " #field7 "=" << ::dbg::detail::format_value(obj.field7) << ", " #field8 "=" << ::dbg::detail::format_value(obj.field8) << "}";          \
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
)                                                            \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
    return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)             \
              << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << ", " #field4 "=" << ::dbg::detail::format_value(obj.field4)                  \
              << ", " #field5 "=" << ::dbg::detail::format_value(obj.field5) << ", " #field6 "=" << ::dbg::detail::format_value(obj.field6)                  \
              << ", " #field7 "=" << ::dbg::detail::format_value(obj.field7) << ", " #field8 "=" << ::dbg::detail::format_value(obj.field8)                  \
              << ", " #field9 "=" << ::dbg::detail::format_value(obj.field9) << "}";                                            \
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
)                                                  \
  inline std::ostream& operator<<(std::ostream& os, const Type& obj) {                             \
    return os << #Type "{" #field1 "=" << ::dbg::detail::format_value(obj.field1) << ", " #field2 "=" << ::dbg::detail::format_value(obj.field2)             \
              << ", " #field3 "=" << ::dbg::detail::format_value(obj.field3) << ", " #field4 "=" << ::dbg::detail::format_value(obj.field4)                  \
              << ", " #field5 "=" << ::dbg::detail::format_value(obj.field5) << ", " #field6 "=" << ::dbg::detail::format_value(obj.field6)                  \
              << ", " #field7 "=" << ::dbg::detail::format_value(obj.field7) << ", " #field8 "=" << ::dbg::detail::format_value(obj.field8)                  \
              << ", " #field9 "=" << ::dbg::detail::format_value(obj.field9) << ", " #field10 "=" << ::dbg::detail::format_value(obj.field10) << "}";        \
  }

// Automatic dispatch macro using buffer arguments
#define DBG_FORMAT_STRUCT(Type, ...)                                                               \
  DBG_FORMAT_STRUCT_DISPATCH(Type, __VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

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
)          \
  DBG_FORMAT_STRUCT##N(Type, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, __VA_ARGS__)

// Or use the direct macros: DBG_FORMAT_STRUCT1 through DBG_FORMAT_STRUCT10
