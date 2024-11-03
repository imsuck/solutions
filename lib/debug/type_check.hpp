#pragma once
#include <iostream>
#include <vector>
using namespace std;

#define ty typename

namespace dbg_internal {
    namespace {
        template<bool...> struct static_all_of;
        template<bool... tail>
        struct static_all_of<true, tail...> : static_all_of<tail...> {};
        template<bool... tail>
        struct static_all_of<false, tail...> : std::false_type {};
        template<> struct static_all_of<> : std::true_type {};
    } // namespace

    template<class T> struct is_vector : false_type {};
    template<class T> struct is_vector<vector<T>> : true_type {};
    template<class T> constexpr bool is_vector_v = is_vector<T>::value;

    template<class T> struct remove_cvref {
        using type = remove_cv_t<remove_reference_t<T>>;
    };
    template<ty T>
    using remove_cvref_t = typename dbg_internal::remove_cvref<T>::type;

    template<ty T> struct streamable {
        template<ty TT>
        static auto test(int) -> decltype(declval<ostream &>() << declval<TT>(),
                                          true_type());
        template<ty> static auto test(...) -> false_type;

        static constexpr bool value = decltype(test<T>(0))::value;
    };
    template<ty T> constexpr bool streamable_v = streamable<T>::value;
    template<ty T> struct iterable {
        template<ty TT>
        static auto test(int) -> decltype(declval<TT>().begin(), true_type());
        template<ty> static auto test(...) -> false_type;

        static constexpr auto value = decltype(test<T>(0))::value;
    };
    template<ty T> constexpr bool iterable_v = iterable<T>::value;

    template<ty T> struct is_trivial;
    template<ty T>
    constexpr bool is_trivial_v = dbg_internal::is_trivial<T>::value;
    template<ty T> struct is_trivial {
        static constexpr bool value =
            conjunction_v<std::is_trivial<T>, is_standard_layout<T>,
                          negation<is_array<T>>>;
    };
    template<ty T, ty U> struct is_trivial<pair<T, U>> {
        static constexpr bool value =
            conjunction_v<dbg_internal::is_trivial<T>,
                          dbg_internal::is_trivial<U>>;
    };
    template<ty... Ts> struct is_trivial<tuple<Ts...>> {
        static constexpr bool value =
            static_all_of<dbg_internal::is_trivial_v<Ts>...>::value;
    };

    template<ty T>
    static constexpr bool _trivial =
        dbg_internal::is_trivial_v<dbg_internal::remove_cvref_t<T>>;
} // namespace dbg_internal

#undef typename
