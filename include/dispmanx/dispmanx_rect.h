#pragma once

#include <type_traits>

#include "bcm_host_type.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    namespace detail {

        template<typename T>
        class dispmanx_rect {
           public:
            static_assert(std::is_same_v<real, T> || std::is_same_v<stub, T>, "T can be detail::stub or detail::real");

            /** \brief Constructs a dispmanx_rect with off_x and off_y being the origin
             * of the rectangle, the width and height being the side lengths of the
             * rectangle
             */
            dispmanx_rect(uint32_t off_x, uint32_t off_y, uint32_t width, uint32_t height);
            /** \brief Constructs a dispmanx_rect which is a exact copy of the provided
             * instance.
             */
            dispmanx_rect(const dispmanx_rect &other) = default;
            /** \brief Move constructs a dispmanx_rect.
             */
            dispmanx_rect(dispmanx_rect &&other) = default;

            /** \brief Sets the width of the rectangle.
             */
            dispmanx_rect &width(uint32_t width);
            /** \brief Sets the height of the rectangle.
             */
            dispmanx_rect &height(uint32_t height);
            /** \brief Sets the x coordinate of the origin of the rectangle.
             */
            dispmanx_rect &off_x(uint32_t off_x);
            /** \brief Sets the y coordinate of the origin of the rectangle.
             */
            dispmanx_rect &off_y(uint32_t off_y);

            /** \brief Observer for the width of the rectangle.
             */
            uint32_t width() const;
            /** \brief Observer for the height of the rectangle.
             */
            uint32_t height() const;
            /** \brief Observer for the x coordinate of the origin of the rectangle.
             */
            uint32_t off_x() const;
            /** \brief Observer for the x coordinate of the origin of the rectangle.
             */
            uint32_t off_y() const;

            /** \brief Returns the underlying struct which can be used by the
             * vc_dispman* calls.
             */
            const VC_RECT_T &rect() const;

           private:
            /** \brief Updates the underlying structure with the current values.
             * This structure is lazily updated, which means it is only updated when
             * needed e.g. retrieved by the rect funtion.
             */
            void update_rect();

            VC_RECT_T m_rect;

            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_off_x;
            uint32_t m_off_y;
            /** \brief Flag which indicates that the values of this instance differ from
             * the values in the underlying structure.
             */
            bool m_changed;
        };

        template<typename T>
        dispmanx_rect<T>::dispmanx_rect(uint32_t off_x, uint32_t off_y, uint32_t width, uint32_t height)
            : m_width(width), m_height(height), m_off_x(off_x), m_off_y(off_y) {
            update_rect();
        }

        template<typename T>
        dispmanx_rect<T> &dispmanx_rect<T>::width(uint32_t width) {
            m_width = width;
            update_rect();

            return *this;
        }

        template<typename T>
        dispmanx_rect<T> &dispmanx_rect<T>::height(uint32_t height) {
            m_height = height;
            update_rect();

            return *this;
        }

        template<typename T>
        dispmanx_rect<T> &dispmanx_rect<T>::off_x(uint32_t off_x) {
            m_off_x = off_x;
            update_rect();

            return *this;
        }

        template<typename T>
        dispmanx_rect<T> &dispmanx_rect<T>::off_y(uint32_t off_y) {
            m_off_y = off_y;
            update_rect();

            return *this;
        }

        template<typename T>
        uint32_t dispmanx_rect<T>::width() const {
            return m_width;
        }

        template<typename T>
        uint32_t dispmanx_rect<T>::height() const {
            return m_height;
        }

        template<typename T>
        uint32_t dispmanx_rect<T>::off_x() const {
            return m_off_x;
        }

        template<typename T>
        uint32_t dispmanx_rect<T>::off_y() const {
            return m_off_y;
        }

        template<typename T>
        void dispmanx_rect<T>::update_rect() {
            vc_dispmanx_rect_set(&m_rect, m_off_x, m_off_y, m_width, m_height);
        }

        template<typename T>
        const VC_RECT_T &dispmanx_rect<T>::rect() const {
            return m_rect;
        }

    }  // namespace detail
    using dispmanx_rect = detail::dispmanx_rect<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
