#pragma once

namespace dbg {
    namespace _detail {
        template<class T>
        inline auto _iter_begin(T &&x, int) -> decltype(x.begin()) {
            return x.begin();
        }
        template<class T>
        inline auto _iter_begin(T &&x, long) -> decltype(begin(x)) {
            return begin(x);
        }
        template<class T>
        inline auto iter_begin(T &&x) -> decltype(_iter_begin(x, 0)) {
            return _iter_begin(x, 0);
        }
    } // namespace _detail
} // namespace dbg
