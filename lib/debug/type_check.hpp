#pragma once

#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "options.hpp"

namespace dbg {
    using namespace std;
    namespace _detail {
        namespace utils {
            template<bool...> struct static_all_of;
            template<bool... tail>
            struct static_all_of<true, tail...> : static_all_of<tail...> {};
            template<bool... tail>
            struct static_all_of<false, tail...> : false_type {};
            template<> struct static_all_of<> : true_type {};

            template<bool...> struct static_any_of;
            template<bool... tail>
            struct static_any_of<true, tail...> : true_type {};
            template<bool... tail>
            struct static_any_of<false, tail...> : static_any_of<tail...> {};
            template<> struct static_any_of<> : false_type {};
        } // namespace utils

        template<typename T, typename... Ts> struct is_any_of {
            static constexpr bool value =
                utils::static_any_of<is_same_v<T, Ts>...>::value;
        };
        template<typename T, typename... Ts>
        inline constexpr bool is_any_of_v = is_any_of<T, Ts...>::value;

        template<typename T> struct remove_cvref {
            using type = remove_cv_t<remove_reference_t<T>>;
        };
        template<typename T>
        using remove_cvref_t = typename remove_cvref<T>::type;

        // Arithmetic ----------------------------------------------------------
        template<typename T> struct is_vec_bool_ref {
            template<typename TT>
            static auto
            test(int) -> enable_if_t<
                          is_same_v<decay_t<TT>, vector<bool>::const_reference>,
                          true_type>;
            template<typename> static auto test(...) -> false_type;

            static constexpr bool value = decltype(test<T>(0))::value;
        };
        template<typename T>
        inline constexpr bool is_arithmetic_v =
            std::is_arithmetic_v<remove_cvref_t<T>> ||
            is_vec_bool_ref<T>::value;
#ifdef __SIZEOF_INT128__
        template<
            typename T,
            enable_if_t<is_any_of_v<remove_cvref_t<T>, __int128_t, __uint128_t>,
                        int> = 1>
        inline constexpr bool is_arithmetic = true;
#endif

        // String --------------------------------------------------------------
        template<typename T>
        inline constexpr bool is_nullptr = is_null_pointer_v<remove_cvref_t<T>>;
        template<typename T>
        inline constexpr bool is_string =
            is_convertible_v<T, string_view> && !is_nullptr<T>;

        // Streamable ----------------------------------------------------------
        template<typename T> struct streamable {
            template<typename TT>
            static auto test(int) -> decltype(declval<ostream>()
                                                  << declval<TT>(),
                                              true_type());
            template<typename TT> static auto test(...) -> false_type;

            static constexpr bool value = decltype(test<T>(0))::value;
        };
        template<typename T>
        inline constexpr bool streamable_v =
            streamable<remove_cvref_t<T>>::value;

        // Pair/tuple ----------------------------------------------------------
        template<typename> struct is_pair : false_type {};
        template<typename T, typename U>
        struct is_pair<pair<T, U>> : true_type {};
        template<typename T>
        inline constexpr bool is_pair_v =
            is_pair<_detail::remove_cvref_t<T>>::value;

        template<typename> struct is_tuple : false_type {};
        template<typename... Args>
        struct is_pair<tuple<Args...>> : true_type {};
        template<typename T>
        inline constexpr bool is_tuple_v =
            is_tuple<_detail::remove_cvref_t<T>>::value;

        // Vector/array --------------------------------------------------------
        template<typename> struct is_vector : false_type {};
        template<typename T, typename... Args>
        struct is_vector<vector<T, Args...>> : true_type {};
        template<typename T>
        inline constexpr bool is_vector_v =
            is_vector<_detail::remove_cvref_t<T>>::value;

        template<typename> struct is_array : false_type {};
        template<typename T, size_t N>
        struct is_array<array<T, N>> : true_type {};
        template<typename T>
        inline constexpr bool is_array_v =
            _detail::is_array<remove_cvref_t<T>>::value;

        // Map -----------------------------------------------------------------
        template<typename> inline constexpr bool _is_map = false;
        template<typename... Args>
        inline constexpr bool _is_map<map<Args...>> = true;
        template<typename... Args>
        inline constexpr bool _is_map<unordered_map<Args...>> = true;

        template<typename T>
        inline constexpr bool is_map = _is_map<remove_cvref_t<T>>;

        // Stack/queue ---------------------------------------------------------
        template<typename> struct is_stack : false_type {};
        template<typename... Args>
        struct is_stack<stack<Args...>> : true_type {};
        template<typename... Args>
        struct is_stack<priority_queue<Args...>> : true_type {}; // for top()
        template<typename T>
        inline constexpr bool is_stack_v = is_stack<remove_cvref_t<T>>::value;

        template<typename> struct is_queue : false_type {};
        template<typename... Args>
        struct is_queue<queue<Args...>> : true_type {};
        template<typename T>
        inline constexpr bool is_queue_v = is_queue<remove_cvref_t<T>>::value;

        // Iterable ------------------------------------------------------------
        template<typename T> struct iterable {
            template<typename TT>
            static auto test(int) -> decltype(declval<TT>().begin(),
                                              true_type());
            template<typename TT> static auto test(...) -> false_type;

            static constexpr bool value = decltype(test<T>(0))::value;
        };
        template<typename T>
        inline constexpr bool iterable_v = iterable<remove_cvref_t<T>>::value;

        // Multiline utility stuff
        template<typename _T, typename T = _detail::remove_cvref_t<_T>>
        struct is_trivial {
            static constexpr bool value =
                (std::is_trivial_v<T> && is_standard_layout_v<T> &&
                 !is_array_v<T>) ||
                (is_string<T> && dbg::options::trivial_string());
        };
        template<typename T, typename U> struct is_trivial<pair<T, U>> {
            static constexpr bool value =
                _detail::is_trivial<T>::value && _detail::is_trivial<U>::value;
        };
        template<typename... Ts> struct is_trivial<tuple<Ts...>> {
            static constexpr bool value =
                utils::static_all_of<_detail::is_trivial<Ts>::value...>::value;
        };
        template<typename T>
        inline constexpr bool is_trivial_v =
            _detail::is_trivial<_detail::remove_cvref_t<T>>::value;
    } // namespace _detail
} // namespace dbg
