#pragma once

namespace dbg {
    namespace options {
        template<typename = void> inline constexpr bool trivial_string() {
            return false;
        };
    }
}
