#pragma once

#include "bcm_host_type.h"
#include "dispmanx_resource.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    enum struct dispmanx_alpha_flags {
        from_source = DISPMANX_FLAGS_ALPHA_FROM_SOURCE,
        fixed_all_pixels = DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS,
        fixed_non_zero = DISPMANX_FLAGS_ALPHA_FIXED_NON_ZERO,
        fixed_exceed_0x07 = DISPMANX_FLAGS_ALPHA_FIXED_EXCEED_0X07,
        premult = DISPMANX_FLAGS_ALPHA_PREMULT,
        mix = DISPMANX_FLAGS_ALPHA_MIX,
        discard_lower_layers = DISPMANX_FLAGS_ALPHA_DISCARD_LOWER_LAYERS,
    };

    namespace detail {

        template<typename T>
        class dispmanx_alpha {
           public:
            dispmanx_alpha(dispmanx_alpha_flags, uint32_t opacity);
            dispmanx_alpha(dispmanx_alpha_flags alpha_flags, uint32_t opacity,
                           const bcm_host_wrapper::dispmanx_resource *resource);

            dispmanx_alpha_flags flags() const;
            uint32_t opacity() const;
            const bcm_host_wrapper::dispmanx_resource *mask() const;

           private:
            dispmanx_alpha_flags m_flags;
            uint32_t m_opacity;
            const bcm_host_wrapper::dispmanx_resource *m_resource;
        };

    }  // namespace detail
    using dispmanx_alpha = detail::dispmanx_alpha<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
