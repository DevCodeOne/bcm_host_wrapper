#pragma once

#include "bcm_host_type.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    namespace detail {

        template<typename T>
        class dispmanx_rect {
           public:
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

    }  // namespace detail
    using dispmanx_rect = detail::dispmanx_rect<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
