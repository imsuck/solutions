#pragma once

#include "containers.hpp"
#include "other.hpp"
#include "trivial.hpp"
#include "type_check.hpp"
#include <string>

namespace dbg {
    namespace _detail {
        template<typename T> string dbg_info(T &&x) {
            if constexpr (is_same_v<remove_cvref_t<T>, bool>) {
                return dbg_bool(x);
            } else if constexpr (is_same_v<remove_cvref_t<T>, char>) {
                return dbg_char(x);
            } else if constexpr (_detail::is_arithmetic_v<T>) {
                return dbg_arithmetic(x);
            } else if constexpr (is_string<T>) {
                return dbg_string(x);
            } else if constexpr (is_pair_v<T>) {
                return dbg_pair(x);
            } else if constexpr (is_tuple_v<T>) {
                return dbg_tuple(x);
            } else if constexpr (is_vector_v<T> || _detail::is_array_v<T>) {
                return dbg_iterable(x, "[", "]");
            } else if constexpr(is_map<T>) {
                return dbg_map(x);
            } else if constexpr (is_stack_v<T>) {
                return dbg_stack(x);
            } else if constexpr (is_queue_v<T>) {
                return dbg_queue(x);
            } else if constexpr (streamable_v<T>) {
                return dbg_streamable(x);
            } else if constexpr (iterable_v<T>) {
                return dbg_iterable(x, "{", "}");
            } else {
                return unsupported_type<T>();
            }
        }
    } // namespace _detail
} // namespace dbg
