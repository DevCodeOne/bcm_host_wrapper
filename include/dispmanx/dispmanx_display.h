#pragma once

#include <optional>
#include <type_traits>

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
            static_assert(std::is_same_v<real, T> || std::is_same_v<stub, T>, "T can be detail::stub or detail::real");

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

        template<typename T>
        std::optional<dispmanx_display<T>> dispmanx_display<T>::open_display(dispmanx_display_ids display_id) {
            auto display = vc_dispmanx_display_open((uint8_t)display_id);

            if (display == 0) {
                return {};
            }

            return dispmanx_display{display};
        }

        template<typename T>
        dispmanx_display<T>::dispmanx_display(DISPMANX_DISPLAY_HANDLE_T &handle) : m_handle(handle) {}

        template<typename T>
        dispmanx_display<T>::dispmanx_display(dispmanx_display &&other) : m_handle(other.m_handle) {
            other.m_handle = 0;
        }

        template<typename T>
        dispmanx_display<T>::~dispmanx_display() {
            if (m_handle != 0) {
                vc_dispmanx_display_close(m_handle);
            }
        }

        template<typename T>
        bcm_host_wrapper::dispmanx_modeinfo dispmanx_display<T>::current_mode() const {
            DISPMANX_MODEINFO_T modeinfo;
            vc_dispmanx_display_get_info(m_handle, &modeinfo);

            return bcm_host_wrapper::dispmanx_modeinfo{modeinfo};
        }

        template<typename T>
        const DISPMANX_DISPLAY_HANDLE_T &dispmanx_display<T>::handle() const {
            return m_handle;
        }

        template<typename T>
        std::optional<bcm_host_wrapper::dispmanx_update> dispmanx_display<T>::start_update(int32_t priority) {
            DISPMANX_UPDATE_HANDLE_T update = vc_dispmanx_update_start(priority);

            if (update == 0) {
                return {};
            }

            return bcm_host_wrapper::dispmanx_update(update, *this);
        }
    }  // namespace detail
    using dispmanx_display = detail::dispmanx_display<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
