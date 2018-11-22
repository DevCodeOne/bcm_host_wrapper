#pragma once

#include "bcm_host_type.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    enum struct dispmanx_display_input_format {
        INVALID = VCOS_DISPLAY_INPUT_FORMAT_INVALID,
        RGB888 = VCOS_DISPLAY_INPUT_FORMAT_RGB888,
        RGB565 = VCOS_DISPLAY_INPUT_FORMAT_RGB565
    };

    namespace detail {

        template<typename T>
        class dispmanx_modeinfo {
           public:
            dispmanx_modeinfo(const dispmanx_modeinfo &other) = default;
            dispmanx_modeinfo(dispmanx_modeinfo &&other) = default;

            inline auto width() const { return m_modeinfo.width; }
            inline auto height() const { return m_modeinfo.height; }
            inline auto display_number() const { return m_modeinfo.display_num; }
            dispmanx_display_input_format input_format() const;

           private:
            dispmanx_modeinfo(const DISPMANX_MODEINFO_T &modeinfo);
            DISPMANX_MODEINFO_T m_modeinfo;

            template<typename T2>
            friend class dispmanx_display;
        };

    }  // namespace detail
    using dispmanx_modeinfo = detail::dispmanx_modeinfo<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
