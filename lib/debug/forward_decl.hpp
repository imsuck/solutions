#pragma once

template<ty T, ty U> str to_str(const pair<T, U> &);
template<ty... Ts> str to_str(const tuple<Ts...> &);
template<ty T> str to_str(const vector<T> &);
template<ty T, size_t N> str to_str(const array<T, N> &);
template<ty T, enable_if_t<dbg_internal::streamable_v<T> &&
                               !is_same_v<decay_t<T>, basic_string<char>>,
                           int>>
str to_str(T &&x);
template<ty T, ty _T,
         enable_if_t<dbg_internal::iterable_v<_T> &&
                         !dbg_internal::is_vector_v<_T> &&
                         !is_same_v<_T, basic_string<char>>,
                     int>>
str to_str(T &&);
