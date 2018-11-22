#pragma once

#include <optional>
#include <type_traits>

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
            static_assert(std::is_same_v<real, T> || std::is_same_v<stub, T>, "T can be detail::stub or detail::real");

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
            dispmanx_update(DISPMANX_UPDATE_HANDLE_T &update_handle, dispmanx_display<T> &display);

            DISPMANX_UPDATE_HANDLE_T m_update;
            dispmanx_display<T> &m_display;
            bool m_submitted = false;

            friend class dispmanx_display<T>;
        };

        // TODO implement and use clamp
        template<typename T>
        inline std::optional<bcm_host_wrapper::dispmanx_element_handle> dispmanx_update<T>::add_element(
            int32_t layer, const bcm_host_wrapper::dispmanx_rect &dest_region,
            const bcm_host_wrapper::dispmanx_resource &resource, const bcm_host_wrapper::dispmanx_rect &src_region,
            const dispmanx_protection &protection, const bcm_host_wrapper::dispmanx_alpha &alpha_wrapper,
            const bcm_host_wrapper::dispmanx_clamp &clamp, const bcm_host_wrapper::dispmanx_transform &transform) {
            // So clamp is not marked as unused
            (void)clamp;
            VC_DISPMANX_ALPHA_T alpha{(int32_t)alpha_wrapper.flags(), (int32_t)alpha_wrapper.opacity(),
                                      alpha_wrapper.mask() ? alpha_wrapper.mask()->handle() : 0};
            DISPMANX_ELEMENT_HANDLE_T handle = vc_dispmanx_element_add(
                m_update, m_display.handle(), layer, &dest_region.rect(), resource.handle(), &src_region.rect(),
                (DISPMANX_PROTECTION_T)protection, &alpha, nullptr, transform.native_transform());

            if (handle == 0) {
                return {};
            }

            return bcm_host_wrapper::dispmanx_element_handle(handle);
        }

        template<>
        inline std::optional<bcm_host_wrapper::dispmanx_element_handle> dispmanx_update<stub>::add_element(
            int32_t, const bcm_host_wrapper::dispmanx_rect &, const bcm_host_wrapper::dispmanx_resource &,
            const bcm_host_wrapper::dispmanx_rect &, const dispmanx_protection &,
            const bcm_host_wrapper::dispmanx_alpha &, const bcm_host_wrapper::dispmanx_clamp &,
            const bcm_host_wrapper::dispmanx_transform &) {
            return {};
        }

        template<typename T>
        dispmanx_update<T>::dispmanx_update(DISPMANX_UPDATE_HANDLE_T &update, dispmanx_display<T> &display)
            : m_update(update), m_display(display) {}

        template<typename T>
        dispmanx_update<T>::dispmanx_update(dispmanx_update &&other)
            : m_update(other.m_update), m_display(other.m_display), m_submitted(other.m_submitted) {
            other.m_update = 0;
        }

        template<typename T>
        dispmanx_update<T>::~dispmanx_update() {
            if (!m_submitted && m_update != 0) {
                submit_update();
            }
        }

        template<typename T>
        void dispmanx_update<T>::change_element_source(const bcm_host_wrapper::dispmanx_element_handle &element,
                                                       bcm_host_wrapper::dispmanx_resource &resource) {
            vc_dispmanx_element_change_source(m_update, element.handle(), resource.handle());
        }

        template<typename T>
        void dispmanx_update<T>::change_element_layer(const bcm_host_wrapper::dispmanx_element_handle &element,
                                                      int32_t layer) {
            vc_dispmanx_element_change_layer(m_update, element.handle(), layer);
        }

        template<typename T>
        void dispmanx_update<T>::signal_element_modification(const bcm_host_wrapper::dispmanx_element_handle &element,
                                                             const bcm_host_wrapper::dispmanx_rect &region) {
            vc_dispmanx_element_modified(m_update, element.handle(), &region.rect());
        }

        template<typename T>
        void dispmanx_update<T>::remove_element(const bcm_host_wrapper::dispmanx_element_handle &element) {
            vc_dispmanx_element_remove(m_update, element.handle());
        }

        template<typename T>
        void dispmanx_update<T>::submit_update() {
            if (m_submitted) {
                return;
            }

            m_submitted = true;
            vc_dispmanx_update_submit_sync(m_update);
        }

    }  // namespace detail
    using dispmanx_update = detail::dispmanx_update<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
