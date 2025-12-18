#pragma once

#include "colors.hpp"
#include "options.hpp"
#include <array>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

namespace dbg {
    namespace detail {
        // Remove cvref helper
        template<typename T>
        using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

        template<typename T> constexpr auto func_name() {
            return __PRETTY_FUNCTION__;
        }

        template<typename T> constexpr auto _type_of_impl() {
            constexpr std::string_view fn_name = func_name<T>();
#if defined(__GNUC__) && !defined(__llvm__)
            return std::string_view{fn_name.data() + 50, fn_name.size() - 51};
#elif defined(__llvm__)
            return std::string_view{fn_name.data() + 35, fn_name.size() - 36};
#else
            return fn_name; // fallback
#endif
        }

        template<typename T> constexpr auto type_of(T &&x) {
            return _type_of_impl<remove_cvref_t<decltype(x)>>();
        }

        template<typename T> constexpr auto type_of() {
            return _type_of_impl<T>();
        }

        template<typename T> std::string unsupported_type() {
            std::string type_name(type_of<T>());
            if (!options::enable_colors) {
                return type_name;
            }
            return to_string(Color::Red) + type_name + to_string(Color::Reset);
        }

        // Type detection helpers
        template<typename T> struct is_string : std::false_type {};
        template<> struct is_string<std::string> : std::true_type {};
        template<> struct is_string<std::string_view> : std::true_type {};
        template<typename... Args>
        struct is_string<std::basic_string<Args...>> : std::true_type {};

        template<typename T> struct is_optional : std::false_type {};
        template<typename T>
        struct is_optional<std::optional<T>> : std::true_type {};

        template<typename T> struct is_tuple : std::false_type {};
        template<typename... Ts>
        struct is_tuple<std::tuple<Ts...>> : std::true_type {};

        template<typename T> struct is_vector : std::false_type {};
        template<typename T, typename A>
        struct is_vector<std::vector<T, A>> : std::true_type {};

        template<typename T> struct is_array : std::false_type {};
        template<typename T, size_t N>
        struct is_array<std::array<T, N>> : std::true_type {};

        template<typename T> struct is_valarray : std::false_type {};
        template<typename T>
        struct is_valarray<std::valarray<T>> : std::true_type {};

        template<typename T> struct is_deque : std::false_type {};
        template<typename T, typename A>
        struct is_deque<std::deque<T, A>> : std::true_type {};

        template<typename T> struct is_queue : std::false_type {};
        template<typename T, typename A>
        struct is_queue<std::queue<T, A>> : std::true_type {};

        template<typename T> struct is_stack : std::false_type {};
        template<typename T, typename A>
        struct is_stack<std::stack<T, A>> : std::true_type {};

        template<typename T> struct is_priority_queue : std::false_type {};
        template<typename C, typename A>
        struct is_priority_queue<
            std::priority_queue<typename C::value_type, C, A>>
            : std::true_type {};

        template<typename T> struct is_set : std::false_type {};
        template<typename T, typename C, typename A>
        struct is_set<std::set<T, C, A>> : std::true_type {};

        template<typename T> struct is_multiset : std::false_type {};
        template<typename T, typename C, typename A>
        struct is_multiset<std::multiset<T, C, A>> : std::true_type {};

        template<typename T> struct is_unordered_set : std::false_type {};
        template<typename T, typename H, typename E, typename A>
        struct is_unordered_set<std::unordered_set<T, H, E, A>>
            : std::true_type {};

        template<typename T> struct is_unordered_multiset : std::false_type {};
        template<typename T, typename H, typename E, typename A>
        struct is_unordered_multiset<std::unordered_multiset<T, H, E, A>>
            : std::true_type {};

        template<typename T> struct is_map : std::false_type {};
        template<typename K, typename V, typename C, typename A>
        struct is_map<std::map<K, V, C, A>> : std::true_type {};

        template<typename T> struct is_multimap : std::false_type {};
        template<typename K, typename V, typename C, typename A>
        struct is_multimap<std::multimap<K, V, C, A>> : std::true_type {};

        template<typename T> struct is_unordered_map : std::false_type {};
        template<typename K, typename V, typename H, typename E, typename A>
        struct is_unordered_map<std::unordered_map<K, V, H, E, A>>
            : std::true_type {};

        template<typename T> struct is_unordered_multimap : std::false_type {};
        template<typename K, typename V, typename H, typename E, typename A>
        struct is_unordered_multimap<std::unordered_multimap<K, V, H, E, A>>
            : std::true_type {};

        template<typename T> struct is_iterator_container : std::false_type {};
        template<typename T>
        struct is_iterator_container<std::vector<T>> : std::true_type {};
        template<typename T>
        struct is_iterator_container<std::deque<T>> : std::true_type {};
        template<typename T>
        struct is_iterator_container<std::list<T>> : std::true_type {};

        template<typename T> struct is_smart_pointer : std::false_type {};
        template<typename T>
        struct is_smart_pointer<std::unique_ptr<T>> : std::true_type {};
        template<typename T>
        struct is_smart_pointer<std::shared_ptr<T>> : std::true_type {};
        template<typename T>
        struct is_smart_pointer<std::weak_ptr<T>> : std::true_type {};

        // Types can opt-in to being considered "simple" by declaring:
        // static constexpr bool is_simple = true;
        template<typename T, typename = void>
        struct is_simple : std::false_type {};

        template<typename T>
        struct is_simple<
            T,
            std::enable_if_t<
                std::is_same_v<decltype(T::is_simple), const bool> &&
                T::is_simple == true>> : std::true_type {};

        template<typename T> struct is_vec_bool_ref : std::false_type {};
        template<>
        struct is_vec_bool_ref<std::vector<bool>::reference> : std::true_type {
        };
    } // namespace detail
} // namespace dbg
