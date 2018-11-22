#pragma once

#include <type_traits>

#include "bcm_host_type.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    namespace detail {
        /** \brief This class is used to identify an element which is used by an
         * dispmanx_update. It doesn't contain any data of the element itself instead it
         * only contains an identifier with which it is possible to modify an
         * dispmanx_element inside an dispmanx_update
         */
        template<typename T>
        class dispmanx_element_handle {
           public:
            static_assert(std::is_same_v<real, T> || std::is_same_v<stub, T>, "T can be detail::stub or detail::real");

            dispmanx_element_handle(dispmanx_element_handle &&other);
            dispmanx_element_handle(const dispmanx_element_handle &other) = delete;

           private:
            dispmanx_element_handle(const DISPMANX_ELEMENT_HANDLE_T &handle);
            const DISPMANX_ELEMENT_HANDLE_T &handle() const;

            DISPMANX_ELEMENT_HANDLE_T m_handle;

            template<typename T2>
            friend class dispmanx_update;
        };

        template<typename T>
        dispmanx_element_handle<T>::dispmanx_element_handle(const DISPMANX_ELEMENT_HANDLE_T &handle)
            : m_handle(handle) {}

        template<typename T>
        dispmanx_element_handle<T>::dispmanx_element_handle(dispmanx_element_handle &&other)
            : m_handle(other.handle()) {
            other.m_handle = 0;
        }

        template<typename T>
        const DISPMANX_ELEMENT_HANDLE_T &dispmanx_element_handle<T>::handle() const {
            return m_handle;
        }

    }  // namespace detail
    using dispmanx_element_handle = detail::dispmanx_element_handle<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
