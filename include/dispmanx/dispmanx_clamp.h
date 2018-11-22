#pragma once

#include "bcm_host_type.h"

namespace bcm_host_wrapper {

    namespace detail {

        // TODO : Implement if needed
        template<typename T>
        class dispmanx_clamp {};

    }  // namespace detail
    using dispmanx_clamp = detail::dispmanx_clamp<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
