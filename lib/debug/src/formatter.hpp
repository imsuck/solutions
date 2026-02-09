#pragma once

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>

#include "colors.hpp"
#include "is_trivial.hpp"
#include "options.hpp"
#include "type_traits.hpp"

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

    namespace detail {
        // Forward declarations
        template<typename T> std::string format_value(const T &value);
        template<typename... Args> std::string format_args(const Args &...args);

        inline std::string indent_str(int level) {
            std::string indent;
            for (int i = 0; i < level; ++i) {
                indent += with_color("▏", Color::Black) + " ";
            }
            return indent;
        }

        // Helper to escape string with colors
        inline std::string escape_string_with_colors(std::string_view str) {
            if (!options::enable_colors) return std::string(str);
            std::string result = to_string(Color::Green); // Start string color

            for (char c : str) {
                std::string escaped;
                bool is_escaped = true;
                switch (c) {
                    case '\'':
                        escaped = "\\'";
                        break;
                    case '\"':
                        escaped = "\\\"";
                        break;
                    case '\\':
                        escaped = "\\\\";
                        break;
                    case '\0':
                        escaped = "\\0";
                        break;
                    case '\a':
                        escaped = "\\a";
                        break;
                    case '\b':
                        escaped = "\\b";
                        break;
                    case '\f':
                        escaped = "\\f";
                        break;
                    case '\n':
                        escaped = "\\n";
                        break;
                    case '\r':
                        escaped = "\\r";
                        break;
                    case '\t':
                        escaped = "\\t";
                        break;
                    case '\v':
                        escaped = "\\v";
                        break;
                    default:
                        if (static_cast<unsigned char>(c) < 32 ||
                            static_cast<unsigned char>(c) > 126) {
                            std::stringstream ss;
                            ss << "\\x" << std::hex << std::setw(2)
                               << std::setfill('0') << (int)(unsigned char)c;
                            escaped = ss.str();
                        } else {
                            is_escaped = false;
                            result += c;
                        }
                }

                if (is_escaped) {
                    result += to_string(Color::Yellow) + escaped +
                              to_string(Color::Green);
                }
            }
            result += to_string(Color::Reset);
            return result;
        }

        // Check if type has operator<<
        template<typename T, typename = void>
        struct has_ostream_operator : std::false_type {};

        template<typename T>
        struct has_ostream_operator<
            T,
            std::void_t<
                decltype(std::declval<std::ostream &>() << std::declval<T>())>>
            : std::true_type {};

        // Format using operator<<
        template<typename T> std::string format_with_ostream(const T &value) {
            std::stringstream ss;
            ss << value;
            return ss.str();
        }

        template<typename T> std::string format_integer(T value) {
            std::string result;
            if constexpr (std::is_same_v<T, __int128_t> ||
                          std::is_same_v<T, __uint128_t>) {
                if (value == 0) {
                    result = "0";
                } else {
                    bool negative = false;
                    if constexpr (std::is_signed_v<T>) {
                        if (value < 0) {
                            negative = true;
                            value = -value;
                        }
                    }
                    while (value > 0) {
                        result.push_back('0' + (value % 10));
                        value /= 10;
                    }
                    if (negative) result.push_back('-');
                    std::reverse(result.begin(), result.end());
                }
            } else {
                result = std::to_string(value);
            }
            // Literals default color
            return result;
        }

        inline std::string format_bool(bool value) {
            return value ? "true" : "false";
        }

        inline std::string format_char(char value) {
            std::string escaped;
            bool is_escaped = true;
            switch (value) {
                case '\'':
                    escaped = "\\'";
                    break;
                case '\"':
                    escaped = "\\\"";
                    break;
                case '\\':
                    escaped = "\\\\";
                    break;
                case '\0':
                    escaped = "\\0";
                    break;
                case '\a':
                    escaped = "\\a";
                    break;
                case '\b':
                    escaped = "\\b";
                    break;
                case '\f':
                    escaped = "\\f";
                    break;
                case '\n':
                    escaped = "\\n";
                    break;
                case '\r':
                    escaped = "\\r";
                    break;
                case '\t':
                    escaped = "\\t";
                    break;
                case '\v':
                    escaped = "\\v";
                    break;
                default:
                    if (static_cast<unsigned char>(value) < 32 ||
                        static_cast<unsigned char>(value) > 126) {
                        std::stringstream ss;
                        ss << "\\x" << std::hex << std::setw(2)
                           << std::setfill('0') << (int)(unsigned char)value;
                        escaped = ss.str();
                    } else {
                        is_escaped = false;
                    }
            }

            if (is_escaped) {
                return "'" + with_color(escaped, Color::Yellow) + "'";
            } else {
                return "'" + std::string(1, value) + "'";
            }
        }

        template<typename T> std::string format_pointer(T *ptr) {
            if (!ptr) return "nullptr";
            // For void pointers, show just the address
            if constexpr (std::is_same_v<std::remove_cv_t<T>, void>) {
                std::stringstream ss;
                ss << ptr;
                return with_color(ss.str(), Color::Yellow);
            } else {
                // Try to format the pointed-to value
                std::string formatted_value = format_value(*ptr);
                // If it's just the unsupported type message, show address
                // instead
                std::string unsupported = unsupported_type<T>();
                if (formatted_value == unsupported) {
                    std::stringstream ss;
                    ss << ptr;
                    return with_color("*" + ss.str(), Color::Yellow);
                } else {
                    return with_color("*", Color::Yellow) + formatted_value;
                }
            }
        }

        template<typename T> std::string format_smart_ptr(const T &ptr) {
            using U = remove_cvref_t<T>;

            // Handle weak_ptr differently
            if constexpr (std::is_same_v<
                              U,
                              std::weak_ptr<typename T::element_type>>) {
                if (ptr.expired()) return "expired";
                // Dereference valid weak_ptr by locking it
                auto locked = ptr.lock();
                return with_color("*", Color::Yellow) + format_value(*locked);
            } else {
                if (!ptr) return "nullptr";
                return with_color("*", Color::Yellow) + format_value(*ptr);
            }
        }

        template<typename T> std::string format_float(T value) {
            std::stringstream ss;
            if (options::fixed_float) {
                ss << std::fixed << std::setprecision(options::float_precision);
            } else {
                ss << std::setprecision(options::float_precision);
            }
            ss << value;
            return ss.str();
        }

        template<typename T>
        std::string format_optional(const std::optional<T> &opt) {
            if (opt.has_value()) {
                return with_color("Some", Color::Cyan) +
                       with_color("(", Color::BrightBlack) +
                       format_value(*opt) + with_color(")", Color::BrightBlack);
            }
            return with_color("None", Color::Red);
        }

        template<typename T> std::string format_string(const T &str) {
            // Handle null C-strings
            if constexpr (std::is_same_v<T, const char *> ||
                          std::is_same_v<T, char *>) {
                if (!str) return with_color("nullptr", Color::Red);
            }
            // Use custom escaping implementation
            if constexpr (std::is_same_v<T, const char *> ||
                          std::is_same_v<T, char *>) {
                return with_color("\"", Color::Green) +
                       escape_string_with_colors(str) +
                       with_color("\"", Color::Green);
            } else {
                return with_color("\"", Color::Green) +
                       escape_string_with_colors(std::string_view(str)) +
                       with_color("\"", Color::Green);
            }
        }

        template<typename... Ts, size_t... Is>
        std::string format_tuple_impl(
            const std::tuple<Ts...> &tup,
            std::index_sequence<Is...>
        ) {
            std::string result = with_color("(", Color::BrightBlack);
            ((result += (Is == 0 ? "" : with_color(", ", Color::BrightBlack)) +
                        format_value(std::get<Is>(tup))),
             ...);
            result += with_color(")", Color::BrightBlack);
            return result;
        }

        template<typename... Ts>
        std::string format_tuple(const std::tuple<Ts...> &tup) {
            return format_tuple_impl(
                tup,
                std::make_index_sequence<sizeof...(Ts)>{}
            );
        }

        template<typename T1, typename T2>
        std::string format_pair(const std::pair<T1, T2> &p) {
            std::string result = with_color("(", Color::BrightBlack);
            result += format_value(p.first);
            result += with_color(", ", Color::BrightBlack);
            result += format_value(p.second);
            result += with_color(")", Color::BrightBlack);
            return result;
        }

        template<typename Container>
        std::string format_array(const Container &cont) {
            using std::begin;
            using std::end;
            auto it = begin(cont);

            std::string result = with_color("[", Color::BrightBlack);
            bool first = true;
            size_t count = 0;

            for (const auto &item : cont) {
                IndentGuard guard;
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::BrightBlack);
                    break;
                }

                if (!first) result += with_color(", ", Color::BrightBlack);
                if (!is_trivial_v(item)) {
                    result +=
                        "\n" + indent_str(IndentGuard::get_current_level());
                }
                result += format_value(item);
                first = false;
                ++count;
            }

            if (!is_trivial_type_v<remove_cvref_t<decltype(*it)>>()) {
                result += "\n" + indent_str(IndentGuard::get_current_level());
            }
            result += with_color("]", Color::BrightBlack);

            return result;
        }

        // Format C-style arrays
        template<typename T> std::string format_c_array(const T &arr) {
            using ElementType = std::remove_extent_t<T>;
            constexpr size_t N = std::extent_v<T>;

            std::string result = with_color("[", Color::BrightBlack);
            bool first = true;
            size_t count = 0;

            for (size_t i = 0; i < N; ++i) {
                IndentGuard guard;
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::BrightBlack);
                    break;
                }

                if (!first) result += with_color(", ", Color::BrightBlack);
                if (!is_trivial_v(arr[i])) {
                    result +=
                        "\n" + indent_str(IndentGuard::get_current_level());
                }
                result += format_value(arr[i]);
                first = false;
                ++count;
            }

            if (!is_trivial_type_v<ElementType>()) {
                result += "\n" + indent_str(IndentGuard::get_current_level());
            }
            result += with_color("]", Color::BrightBlack);

            return result;
        }

        template<typename Container>
        std::string format_brace_container(const Container &cont) {
            std::string result = with_color("{", Color::BrightBlack);
            bool first = true;
            size_t count = 0;

            for (const auto &item : cont) {
                IndentGuard guard;
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::BrightBlack);
                    break;
                }

                if (!first) result += with_color(", ", Color::BrightBlack);
                if (!is_trivial_v(item)) {
                    result +=
                        "\n" + indent_str(IndentGuard::get_current_level());
                }
                result += format_value(item);
                first = false;
                ++count;
            }

            if (!is_trivial_type_v<typename Container::value_type>()) {
                result += "\n" + indent_str(IndentGuard::get_current_level());
            }
            result += with_color("}", Color::BrightBlack);

            return result;
        }

        // Format deque (front to back)
        template<typename Container>
        std::string format_deque(const Container &cont) {
            return format_brace_container(cont);
        }

        // Format queue (front to back)
        template<typename T, typename A>
        std::string format_queue(const std::queue<T, A> &cont) {
            std::string result = with_color("{", Color::BrightBlack);
            std::queue<T, A> temp = cont;

            bool first = true;
            while (!temp.empty()) {
                if (!first) result += with_color(", ", Color::BrightBlack);
                result += format_value(temp.front());
                temp.pop();
                first = false;
            }
            result += with_color("}", Color::BrightBlack);

            return result;
        }

        // Format stack/priority_queue (top to bottom)
        template<typename T, typename A>
        std::string format_stack(const std::stack<T, A> &cont) {
            std::string result = with_color("{", Color::BrightBlack);
            std::stack<T, A> temp = cont;

            bool first = true;
            while (!temp.empty()) {
                if (!first) result += with_color(", ", Color::BrightBlack);
                result += format_value(temp.top());
                temp.pop();
                first = false;
            }
            result += with_color("}", Color::BrightBlack);

            return result;
        }

        // Format priority_queue (top to bottom)
        template<typename T, typename C, typename A>
        std::string
        format_priority_queue(const std::priority_queue<T, C, A> &cont) {
            std::string result = with_color("{", Color::BrightBlack);
            std::priority_queue<T, C, A> temp = cont;

            bool first = true;
            while (!temp.empty()) {
                if (!first) result += with_color(", ", Color::BrightBlack);
                result += format_value(temp.top());
                temp.pop();
                first = false;
            }
            result += with_color("}", Color::BrightBlack);

            return result;
        }

        template<typename Container>
        std::string format_set(const Container &cont) {
            return format_brace_container(cont);
        }

        template<typename Container>
        std::string format_multiset(const Container &cont) {
            if (!options::show_multiplicity) {
                return format_brace_container(cont);
            }

            std::string result = with_color("{", Color::BrightBlack);
            bool first = true;
            size_t count = 0;

            auto it = cont.begin();
            while (it != cont.end()) {
                IndentGuard guard;
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::BrightBlack);
                    break;
                }

                auto range = cont.equal_range(*it);
                size_t multiplicity = std::distance(range.first, range.second);

                if (!first) result += with_color(", ", Color::BrightBlack);
                if (!is_trivial_v(*it)) {
                    result +=
                        "\n" + indent_str(IndentGuard::get_current_level());
                }

                result += format_value(*it);
                if (multiplicity > 1) {
                    result += with_color(
                        " (" + std::to_string(multiplicity) + ")",
                        Color::BrightBlack
                    );
                }

                first = false;
                it = range.second;
                ++count;
            }

            if (!is_trivial_type_v<typename Container::value_type>()) {
                result += "\n" + indent_str(IndentGuard::get_current_level());
            }
            result += with_color("}", Color::BrightBlack);

            return result;
        }

        template<typename Map> std::string format_map(const Map &map) {
            std::string result = with_color("{", Color::BrightBlack);
            bool first = true;
            size_t count = 0;

            for (const auto &[key, value] : map) {
                IndentGuard guard;
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::BrightBlack);
                    break;
                }

                if (!first) result += with_color(",", Color::BrightBlack);
                result += "\n" + indent_str(IndentGuard::get_current_level());
                result += format_value(key) +
                          with_color(" -> ", Color::BrightBlack) +
                          format_value(value);
                first = false;
                ++count;
            }

            result += "\n" + indent_str(IndentGuard::get_current_level()) +
                      with_color("}", Color::BrightBlack);
            return result;
        }

        template<typename Map> std::string format_multimap(const Map &map) {
            if (!options::show_multiplicity) {
                return format_map(map);
            }

            std::string result = with_color("{", Color::BrightBlack);
            bool first = true;
            size_t count = 0;

            auto it = map.begin();
            while (it != map.end()) {
                IndentGuard guard;
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::BrightBlack);
                    break;
                }

                auto range = map.equal_range(it->first);
                size_t multiplicity = std::distance(range.first, range.second);

                if (!first) result += with_color(",", Color::BrightBlack);
                result += "\n" + indent_str(IndentGuard::get_current_level());
                result += format_value(it->first);

                if (multiplicity > 1) {
                    result += with_color(
                        " (" + std::to_string(multiplicity) + ")",
                        Color::BrightBlack
                    );
                }

                result += with_color(" -> ", Color::BrightBlack);
                std::vector<decltype(*it->second)> values;
                values.reserve(multiplicity);
                for (auto val_it = range.first; val_it != range.second;
                     ++val_it) {
                    values.push_back(val_it->second);
                }
                result += format_value(values);

                // result += with_color(" -> [", Color::BrightBlack);
                // bool value_first = true;
                // for (auto val_it = range.first; val_it != range.second;
                //      ++val_it) {
                //     IndentGuard guard2;
                //     if (!value_first)
                //         result += with_color(", ", Color::BrightBlack);
                //     result += format_value(val_it->second);
                //     value_first = false;
                // }
                // result += with_color("]", Color::BrightBlack);

                first = false;
                it = range.second;
                ++count;
            }

            result += "\n" + indent_str(IndentGuard::get_current_level()) +
                      with_color("}", Color::BrightBlack);
            return result;
        }

        template<typename T> std::string format_bitset(const T &bs) {
            return bs.to_string();
        }

        template<typename T> std::string format_value(const T &value) {
            using U = remove_cvref_t<T>;

            // Built-in types - check char types before integral
            if constexpr (std::is_same_v<U, char> ||
                          std::is_same_v<U, signed char> ||
                          std::is_same_v<U, unsigned char> ||
                          std::is_same_v<U, wchar_t> ||
                          std::is_same_v<U, char16_t> ||
                          std::is_same_v<U, char32_t>) {
                return format_char(value);
            } else if constexpr (std::is_same_v<U, bool>) {
                return format_bool(value);
            } else if constexpr (
#ifdef __GNUC__
                                 std::is_same_v<U, __int128_t> ||
                                 std::is_same_v<U, __uint128_t> ||
                                 std::is_same_v<U, __int128> ||
                                 std::is_same_v<U, unsigned __int128> ||
#endif
                                 false) {
                return format_integer(value);
            } else if constexpr (std::is_integral_v<U>) {
                return format_integer(value);
            } else if constexpr (std::is_floating_point_v<U>) {
                return format_float(value);
            }
            // String types (including C-style strings and string literals) -
            // check before pointers
            else if constexpr (is_string<U>::value ||
                               std::is_same_v<U, const char *> ||
                               std::is_same_v<U, char *> ||
                               (std::is_array_v<U> &&
                                std::
                                    is_same_v<std::remove_extent_t<U>, char>) ||
                               (std::is_array_v<U> &&
                                std::is_same_v<
                                    std::remove_extent_t<U>,
                                    wchar_t>) ||
                               (std::is_array_v<U> &&
                                std::is_same_v<
                                    std::remove_extent_t<U>,
                                    char16_t>) ||
                               (std::is_array_v<U> &&
                                std::is_same_v<
                                    std::remove_extent_t<U>,
                                    char32_t>)) {
                return format_string(value);
            } else if constexpr (std::is_pointer_v<U>) {
                return format_pointer(value);
            }
            // Smart pointers
            else if constexpr (is_smart_pointer<U>::value) {
                return format_smart_ptr(value);
            }
            // Optional
            else if constexpr (is_optional<U>::value) {
                return format_optional(value);
            }
            // Pair
            else if constexpr (is_pair<U>::value) {
                return format_pair(value);
            }
            // Tuple
            else if constexpr (is_tuple<U>::value) {
                return format_tuple(value);
            }
            // Vector-like containers
            else if constexpr (is_vector<U>::value || is_array<U>::value ||
                               is_valarray<U>::value) {
                return format_array(value);
            }
            // C-style arrays
            else if constexpr (std::is_array_v<U>) {
                return format_c_array(value);
            }
            // Deque
            else if constexpr (is_deque<U>::value) {
                return format_deque(value);
            }
            // Queue
            else if constexpr (is_queue<U>::value) {
                return format_queue(value);
            }
            // Stack
            else if constexpr (is_stack<U>::value) {
                return format_stack(value);
            }
            // Priority Queue
            else if constexpr (is_priority_queue<U>::value) {
                return format_priority_queue(value);
            }
            // Sets
            else if constexpr (is_set<U>::value || is_unordered_set<U>::value) {
                return format_set(value);
            }
            // Multisets
            else if constexpr (is_multiset<U>::value ||
                               is_unordered_multiset<U>::value) {
                return format_multiset(value);
            }
            // Maps
            else if constexpr (is_map<U>::value || is_unordered_map<U>::value) {
                return format_map(value);
            }
            // Multimaps
            else if constexpr (is_multimap<U>::value ||
                               is_unordered_multimap<U>::value) {
                return format_multimap(value);
            }
            // Bitset
            else if constexpr (is_bitset<U>::value) {
                return format_bitset(value);
            }
            // Iterator-based containers (fallback)
            else if constexpr (is_iterator_container<U>::value) {
                return format_array(value);
            }
            // Types with operator<<
            else if constexpr (has_ostream_operator<U>::value) {
                return format_with_ostream(value);
            } else {
                return unsupported_type<T>();
            }
        }
    } // namespace detail
} // namespace dbg
