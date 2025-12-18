#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <optional>
#include <tuple>
#include <valarray>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <utility>
#include <memory>

#include "src/options.hpp"
#include "src/colors.hpp"
#include "src/type_traits.hpp"
#include "src/is_trivial.hpp"
#include "src/formatter.hpp"
#include "src/debug_core.hpp"

#define dbg(...) DBG_CHOOSE_MACRO(DBG_COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)
#define debug()
