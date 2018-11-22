#pragma once

#include <optional>

#include "bcm_host_type.h"
#include "dispmanx/dispmanx_alpha.h"
#include "dispmanx/dispmanx_clamp.h"
#include "dispmanx/dispmanx_element_handle.h"
#include "dispmanx/dispmanx_rect.h"
#include "dispmanx/dispmanx_resource.h"
#include "dispmanx/dispmanx_transform.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    enum struct dispmanx_protection {
        MAX = DISPMANX_PROTECTION_MAX,
        NONE = DISPMANX_PROTECTION_NONE,
        HDCP = DISPMANX_PROTECTION_HDCP
    };

    namespace detail {

        template<typename T>
        class dispmanx_display;

        template<typename T>
        class dispmanx_update {
           public:
            dispmanx_update(const dispmanx_update &) = delete;
            dispmanx_update(dispmanx_update &&);
            ~dispmanx_update();

            std::optional<bcm_host_wrapper::dispmanx_element_handle> add_element(
                int32_t layer, const bcm_host_wrapper::dispmanx_rect &dest_region,
                const bcm_host_wrapper::dispmanx_resource &resource, const bcm_host_wrapper::dispmanx_rect &src_region,
                const bcm_host_wrapper::dispmanx_protection &protection, const bcm_host_wrapper::dispmanx_alpha &alpha,
                const bcm_host_wrapper::dispmanx_clamp &clamp, const bcm_host_wrapper::dispmanx_transform &transform);
            void change_element_source(const bcm_host_wrapper::dispmanx_element_handle &element,
                                       bcm_host_wrapper::dispmanx_resource &resource);
            void change_element_layer(const bcm_host_wrapper::dispmanx_element_handle &element, int32_t layer);
            void signal_element_modification(const bcm_host_wrapper::dispmanx_element_handle &element,
                                             const bcm_host_wrapper::dispmanx_rect &region);
            void remove_element(const bcm_host_wrapper::dispmanx_element_handle &element);
            void submit_update();

           private:
            dispmanx_update(DISPMANX_UPDATE_HANDLE_T &update_handle, dispmanx_display<bcm_host_type> &display);

            DISPMANX_UPDATE_HANDLE_T m_update;
            dispmanx_display<bcm_host_type> &m_display;
            bool m_submitted = false;

            template<typename T2>
            friend class dispmanx_display;
        };

    }  // namespace detail
    using dispmanx_update = detail::dispmanx_update<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
