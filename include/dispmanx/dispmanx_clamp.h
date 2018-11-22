#pragma once

#include <type_traits>

#include "bcm_host_type.h"

namespace bcm_host_wrapper {

    namespace detail {

        // TODO : Implement if needed
        template<typename T>
        class dispmanx_clamp {
            static_assert(std::is_same_v<real, T> || std::is_same_v<stub, T>, "T can be detail::stub or detail::real");
        };

    }  // namespace detail
    using dispmanx_clamp = detail::dispmanx_clamp<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
