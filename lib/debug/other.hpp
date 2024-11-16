#pragma once

#include <string>
#include <string_view>

namespace dbg {
    using namespace std;
    namespace _detail {
        template<typename T> constexpr auto func_name() {
            return __PRETTY_FUNCTION__;
        }
        template<typename T> constexpr auto _type_of_impl() {
            constexpr string_view fn_name = func_name<T>();
#if defined(__GNUC__) && !defined(__llvm__)
            return string_view{fn_name.data() + 51, fn_name.size() - 52};
#elif defined(__llvm__)
            return string_view{fn_name.data() + 36, fn_name.size() - 37};
#endif
        }
        template<typename T> constexpr auto type_of(T &&x) {
            return _type_of_impl<decltype(x)>();
        }
        template<typename T> constexpr auto type_of() {
            return _type_of_impl<T>();
        }

        template<typename T> string unsupported_type() {
            return "\e[31m[" + string(type_of<T>()) + "]\e[0m";
        }
    } // namespace _detail
} // namespace dbg
