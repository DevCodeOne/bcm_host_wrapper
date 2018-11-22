#pragma once

#include <optional>

#include "bcm_host_type.h"
#include "dispmanx/dispmanx_modeinfo.h"
#include "dispmanx/dispmanx_update.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    enum struct dispmanx_display_ids : uint8_t {
        MAIN_LCD = DISPMANX_ID_MAIN_LCD,
        AUX_LCD = DISPMANX_ID_AUX_LCD,
        HDMI = DISPMANX_ID_HDMI,
        SDTV = DISPMANX_ID_SDTV,
        FORCE_LCD = DISPMANX_ID_FORCE_LCD,
        FORCE_TV = DISPMANX_ID_FORCE_TV,
        FORCE_OTHER = DISPMANX_ID_FORCE_OTHER
    };

    namespace detail {

        template<typename T>
        class dispmanx_display {
           public:
            dispmanx_display(const dispmanx_display &other) = delete;
            dispmanx_display(dispmanx_display &&other);
            ~dispmanx_display();

            static std::optional<dispmanx_display> open_display(dispmanx_display_ids display_id);

            std::optional<bcm_host_wrapper::dispmanx_update> start_update(int32_t priority = 0);

            bcm_host_wrapper::dispmanx_modeinfo current_mode() const;

           private:
            dispmanx_display(DISPMANX_DISPLAY_HANDLE_T &display_handle);
            const DISPMANX_DISPLAY_HANDLE_T &handle() const;

            DISPMANX_DISPLAY_HANDLE_T m_handle;

            template<typename T2>
            friend class dispmanx_update;
        };

    }  // namespace detail
    using dispmanx_display = detail::dispmanx_display<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
