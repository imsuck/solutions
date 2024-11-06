#pragma once

#include <string>

namespace dbg {
    using namespace std;
    namespace _detail {
        template<typename T> string dbg_info(T &&);
    }
} // namespace dbg

