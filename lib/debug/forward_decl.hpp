#pragma once

template<ty T, ty U> str to_str(const pair<T, U> &);
template<ty... Ts> str to_str(const tuple<Ts...> &);
template<ty T> str to_str(const vector<T> &);
template<ty T, size_t N> str to_str(const array<T, N> &);
template<ty T, enable_if_t<dbg_internal::streamable_v<T>, int>>
str to_str(T &&);
template<ty T, enable_if_t<dbg_internal::iterable_v<T>, int>> str to_str(T &&);

