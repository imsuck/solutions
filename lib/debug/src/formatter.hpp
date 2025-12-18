#pragma once

#include "colors.hpp"
#include "is_trivial.hpp"
#include "options.hpp"
#include "type_traits.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace dbg {
    namespace detail {
        // Forward declarations
        template<typename T>
        std::string format_value(const T &value, int indent = 0);
        template<typename... Args> std::string format_args(const Args &...args);

        std::string indent_str(int level) {
            return std::string(level * 2, ' ');
        }

        inline std::string with_color(const std::string &value, Color color) {
            if (!options::enable_colors) {
                return value;
            }
            return to_string(color) + value + to_string(Color::Reset);
        }

        // Custom formatter registry
        namespace detail {
            using CustomFormatter = std::function<std::string(const void *)>;
            inline std::unordered_map<size_t, CustomFormatter>
                custom_formatters;

            template<typename T> std::string format_custom(const T &value) {
                auto it = custom_formatters.find(typeid(T).hash_code());
                if (it != custom_formatters.end()) {
                    return it->second(&value);
                }
                return unsupported_type<T>();
            }
        } // namespace detail

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
            return with_color(result, Color::Yellow);
        }

        inline std::string format_bool(bool value) {
            return with_color(value ? "true" : "false", Color::Yellow);
        }

        inline std::string format_char(char value) {
            std::string result;
            if (value >= 32 && value <= 126) {
                result = "'" + std::string(1, value) + "'";
            } else {
                // For non-printable characters, show as integer
                result = std::to_string(static_cast<int>(value));
            }
            return with_color(result, Color::Cyan);
        }

        template<typename T> std::string format_pointer(T *ptr) {
            if (!ptr) return "nullptr";
            // For void pointers, show just the address
            if constexpr (std::is_same_v<std::remove_cv_t<T>, void>) {
                std::stringstream ss;
                ss << ptr;
                return ss.str();
            } else {
                // Try to format the pointed-to value
                std::string formatted_value = format_value(*ptr);
                // If it's just the unsupported type message, show address instead
                std::string unsupported = unsupported_type<T>();
                if (formatted_value == unsupported) {
                    std::stringstream ss;
                    ss << ptr;
                    return "*" + ss.str();
                } else {
                    return "*" + formatted_value;
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
                return "*" + format_value(*locked);
            } else {
                if (!ptr) return "nullptr";
                return "*" + format_value(*ptr);
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
            return with_color(ss.str(), Color::Yellow);
        }

        template<typename T>
        std::string format_optional(const std::optional<T> &opt) {
            if (opt.has_value()) {
                return with_color("Some", Color::Cyan) +
                       with_color("(", Color::Reset) + format_value(*opt) +
                       with_color(")", Color::Reset);
            }
            return with_color("None", Color::Red);
        }

        template<typename T> std::string format_string(const T &str) {
            // Handle null C-strings
            if constexpr (std::is_same_v<T, const char *> ||
                          std::is_same_v<T, char *>) {
                if (!str) return with_color("nullptr", Color::Red);
            }
            return with_color("\"" + std::string(str) + "\"", Color::Green);
        }

        template<typename... Ts, size_t... Is>
        std::string format_tuple_impl(
            const std::tuple<Ts...> &tup,
            std::index_sequence<Is...>
        ) {
            std::string result = with_color("(", Color::White);
            ((result += (Is == 0 ? "" : with_color(", ", Color::White)) +
                        format_value(std::get<Is>(tup))),
             ...);
            result += with_color(")", Color::White);
            return result;
        }

        template<typename... Ts>
        std::string format_tuple(const std::tuple<Ts...> &tup) {
            return format_tuple_impl(
                tup,
                std::make_index_sequence<sizeof...(Ts)>{}
            );
        }

        template<typename Container>
        std::string format_array(const Container &cont, int indent = 0) {
            if (cont.empty()) return with_color("[]", Color::White);

            std::string result = with_color("[", Color::White);
            bool first = true;
            size_t count = 0;

            for (const auto &item : cont) {
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::White);
                    break;
                }

                if (!first) result += with_color(", ", Color::White);
                if (!is_trivial_v(item)) {
                    result += "\n" + indent_str(indent + 1);
                }
                result += format_value(item, indent + 1);
                first = false;
                ++count;
            }

            if (!is_trivial_type_v<typename Container::value_type>()) {
                result += "\n" + indent_str(indent);
            }
            result += with_color("]", Color::White);

            return result;
        }

        // Format C-style arrays
        template<typename T>
        std::string format_c_array(const T &arr, int indent = 0) {
            using ElementType = std::remove_extent_t<T>;
            constexpr size_t N = std::extent_v<T>;

            if (N == 0) return with_color("[]", Color::White);

            std::string result = with_color("[", Color::White);
            bool first = true;
            size_t count = 0;

            for (size_t i = 0; i < N; ++i) {
                if (options::max_container_elements != -1 &&
                    count >= static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::White);
                    break;
                }

                if (!first) result += with_color(", ", Color::White);
                if (!is_trivial_v(arr[i])) {
                    result += "\n" + indent_str(indent + 1);
                }
                result += format_value(arr[i], indent + 1);
                first = false;
                ++count;
            }

            if (!is_trivial_type_v<ElementType>()) {
                result += "\n" + indent_str(indent);
            }
            result += with_color("]", Color::White);

            return result;
        }

        template<typename Container>
        std::string
        format_brace_container(const Container &cont, int indent = 0) {
            if (cont.empty()) return with_color("{}", Color::White);

            std::string result = with_color("{", Color::White);
            bool first = true;
            size_t count = 0;

            for (const auto &item : cont) {
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::White);
                    break;
                }

                if (!first) result += with_color(", ", Color::White);
                if (!is_trivial_v(item)) {
                    result += "\n" + indent_str(indent + 1);
                }
                result += format_value(item, indent + 1);
                first = false;
                ++count;
            }

            if (!is_trivial_type_v<typename Container::value_type>()) {
                result += "\n" + indent_str(indent);
            }
            result += with_color("}", Color::White);

            return result;
        }

        // Format deque (front to back)
        template<typename Container>
        std::string format_deque(const Container &cont, int indent = 0) {
            return format_brace_container(cont, indent);
        }

        // Format queue (front to back)
        template<typename T, typename A>
        std::string format_queue(const std::queue<T, A> &cont, int indent = 0) {
            if (cont.empty()) return "{}";

            std::string result = "{";
            std::queue<T, A> temp = cont;

            bool first = true;
            while (!temp.empty()) {
                if (!first) result += ", ";
                result += format_value(temp.front(), indent);
                temp.pop();
                first = false;
            }
            result += "}";

            return result;
        }

        // Format stack/priority_queue (top to bottom)
        template<typename T, typename A>
        std::string format_stack(const std::stack<T, A> &cont, int indent = 0) {
            if (cont.empty()) return "{}";

            std::string result = "{";
            std::stack<T, A> temp = cont;

            bool first = true;
            while (!temp.empty()) {
                if (!first) result += ", ";
                result += format_value(temp.top(), indent);
                temp.pop();
                first = false;
            }
            result += "}";

            return result;
        }

        // Format priority_queue (top to bottom)
        template<typename T, typename C, typename A>
        std::string format_priority_queue(
            const std::priority_queue<T, C, A> &cont,
            int indent = 0
        ) {
            if (cont.empty()) return "{}";

            std::string result = "{";
            std::priority_queue<T, C, A> temp = cont;

            bool first = true;
            while (!temp.empty()) {
                if (!first) result += ", ";
                result += format_value(temp.top(), indent);
                temp.pop();
                first = false;
            }
            result += "}";

            return result;
        }

        template<typename Container>
        std::string format_set(const Container &cont, int indent = 0) {
            return format_brace_container(cont, indent);
        }

        template<typename Container>
        std::string format_multiset(const Container &cont, int indent = 0) {
            if (cont.empty()) return "{}";

            if (!options::show_multiplicity) {
                return format_brace_container(cont, indent);
            }

            std::string result = "{";
            bool first = true;
            size_t count = 0;

            auto it = cont.begin();
            while (it != cont.end()) {
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += ", ...";
                    break;
                }

                auto range = cont.equal_range(*it);
                size_t multiplicity = std::distance(range.first, range.second);

                if (!first) result += ", ";
                if (!is_trivial_v(*it)) {
                    result += "\n" + indent_str(indent + 1);
                }

                result += format_value(*it, indent + 1);
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
                result += "\n" + indent_str(indent);
            }
            result += "}";

            return result;
        }

        template<typename Map>
        std::string format_map(const Map &map, int indent = 0) {
            if (map.empty()) return with_color("{}", Color::White);

            std::string result = with_color("{", Color::White);
            bool first = true;
            size_t count = 0;

            for (const auto &[key, value] : map) {
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += with_color(", ...", Color::White);
                    break;
                }

                if (!first) result += with_color(",", Color::White);
                result += "\n" + indent_str(indent + 1);
                result += format_value(key, indent + 1) +
                          with_color(" -> ", Color::White) +
                          format_value(value, indent + 1);
                first = false;
                ++count;
            }

            result += "\n" + indent_str(indent) + with_color("}", Color::White);
            return result;
        }

        template<typename Map>
        std::string format_multimap(const Map &map, int indent = 0) {
            if (map.empty()) return "{}";

            if (!options::show_multiplicity) {
                return format_map(map, indent);
            }

            std::string result = "{";
            bool first = true;
            size_t count = 0;

            auto it = map.begin();
            while (it != map.end()) {
                if (options::max_container_elements != -1 &&
                    count >=
                        static_cast<size_t>(options::max_container_elements)) {
                    result += ", ...";
                    break;
                }

                auto range = map.equal_range(it->first);
                size_t multiplicity = std::distance(range.first, range.second);

                if (!first) result += ",";
                result += "\n" + indent_str(indent + 1);
                result += format_value(it->first, indent + 1);

                if (multiplicity > 1) {
                    result += with_color(
                        " (" + std::to_string(multiplicity) + ")",
                        Color::BrightBlack
                    );
                }

                result += " -> [";
                bool value_first = true;
                for (auto val_it = range.first; val_it != range.second;
                     ++val_it) {
                    if (!value_first) result += ", ";
                    result += format_value(val_it->second, indent + 2);
                    value_first = false;
                }
                result += "]";

                first = false;
                it = range.second;
                ++count;
            }

            result += "\n" + indent_str(indent) + "}";
            return result;
        }

        template<typename T>
        std::string format_value(const T &value, int indent) {
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
            // String types (including C-style strings and string literals) - check before pointers
            else if constexpr (is_string<U>::value ||
                               std::is_same_v<U, const char *> ||
                               std::is_same_v<U, char *> ||
                               (std::is_array_v<U> && std::is_same_v<std::remove_extent_t<U>, char>) ||
                               (std::is_array_v<U> && std::is_same_v<std::remove_extent_t<U>, wchar_t>) ||
                               (std::is_array_v<U> && std::is_same_v<std::remove_extent_t<U>, char16_t>) ||
                               (std::is_array_v<U> && std::is_same_v<std::remove_extent_t<U>, char32_t>)) {
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
            // Tuple
            else if constexpr (is_tuple<U>::value) {
                return format_tuple(value);
            }
            // Vector-like containers
            else if constexpr (is_vector<U>::value || is_array<U>::value ||
                               is_valarray<U>::value) {
                return format_array(value, indent);
            }
            // C-style arrays
            else if constexpr (std::is_array_v<U>) {
                return format_c_array(value, indent);
            }
            // Deque
            else if constexpr (is_deque<U>::value) {
                return format_deque(value, indent);
            }
            // Queue
            else if constexpr (is_queue<U>::value) {
                return format_queue(value, indent);
            }
            // Stack
            else if constexpr (is_stack<U>::value) {
                return format_stack(value, indent);
            }
            // Priority Queue
            else if constexpr (is_priority_queue<U>::value) {
                return format_priority_queue(value, indent);
            }
            // Sets
            else if constexpr (is_set<U>::value || is_unordered_set<U>::value) {
                return format_set(value, indent);
            }
            // Multisets
            else if constexpr (is_multiset<U>::value ||
                               is_unordered_multiset<U>::value) {
                return format_multiset(value, indent);
            }
            // Maps
            else if constexpr (is_map<U>::value || is_unordered_map<U>::value) {
                return format_map(value, indent);
            }
            // Multimaps
            else if constexpr (is_multimap<U>::value ||
                               is_unordered_multimap<U>::value) {
                return format_multimap(value, indent);
            }
            // Iterator-based containers (fallback)
            else if constexpr (is_iterator_container<U>::value) {
                return format_array(value, indent);
            }
            // Types with operator<<
            else if constexpr (has_ostream_operator<U>::value) {
                return format_with_ostream(value);
            } else {
                return detail::format_custom(value);
            }
        }
    } // namespace detail
} // namespace dbg
