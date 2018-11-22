#pragma once

#include <cstdint>
#include <memory>
#include <type_traits>

#include "bcm_host_type.h"
#include "dispmanx_resource.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    namespace detail {

        /** \brief This class is used when raw pixel values should be loaded into a
         * dispmanx_resource. This class automaticly chooses a suitable size for the
         * underlying array. It also calculates the correct pitch. If the underlying
         * array doesn't have dimensions which aren't divisable by 16 the function which
         * uploades the pixels to a dispmanx_resource won't finish
         */
        template<typename T, typename color_type, typename size_type>
        class dispmanx_pixmap {
           public:
            static_assert(std::is_same_v<real, T> || std::is_same_v<stub, T>, "T can be detail::stub or detail::real");

            /** \brief Constructs a dispmanx_pixmap with dimensions which are at least
             * widthxheight. The class will round the dimensions up to numbers which are
             * divisable by 16 so that the functions which upload the data from the
             * pixmap to the resource will work.
             */
            dispmanx_pixmap(size_type width, size_type height);

            /** \brief Returns row with index.
             */
            const color_type *operator[](size_type index) const;
            /** \brief Returns row with index.
             */
            color_type *operator[](size_type index);

            /** \brief Returns the whole underlying array.
             */
            const color_type *data() const;

            /** \brief Returns the real width of the pixmap.
             */
            size_type width() const;
            /** \brief Returns the real pitch of the pixmap which is the number of
             * entries until the next row of the pixmap.
             */
            size_type pitch() const;
            /** \brief Returns the real height of the pixmap.
             */
            size_type height() const;

           private:
            size_type m_width;
            size_type m_height;
            size_type m_pitch;
            std::unique_ptr<color_type[]> m_data;

            /** \brief Function which calculates the next number which is greater or
             * equal to this value and is divisable by 16.
             */
            template<size_type align_to>
            static constexpr size_type align(const size_type length);
        };

        template<typename T, typename color_type, typename size_type>
        dispmanx_pixmap<T, color_type, size_type>::dispmanx_pixmap(size_type width, size_type height)
            : m_width(width), m_height(height), m_pitch(align<16>(width)) {
            m_data = std::make_unique<color_type[]>(m_pitch * m_height);
        }

        template<typename T, typename color_type, typename size_type>
        template<size_type align_to>
        constexpr size_type dispmanx_pixmap<T, color_type, size_type>::align(const size_type length) {
            return (length + (align_to - 1)) & (~(align_to - 1));
        }

        template<typename T, typename color_type, typename size_type>
        size_type dispmanx_pixmap<T, color_type, size_type>::width() const {
            return m_width;
        }

        template<typename T, typename color_type, typename size_type>
        size_type dispmanx_pixmap<T, color_type, size_type>::height() const {
            return m_height;
        }

        template<typename T, typename color_type, typename size_type>
        size_type dispmanx_pixmap<T, color_type, size_type>::pitch() const {
            return m_pitch;
        }

        template<typename T, typename color_type, typename size_type>
        const color_type *dispmanx_pixmap<T, color_type, size_type>::operator[](size_type index) const {
            return m_data.get() + index * pitch();
        }

        template<typename T, typename color_type, typename size_type>
        color_type *dispmanx_pixmap<T, color_type, size_type>::operator[](size_type index) {
            return m_data.get() + index * pitch();
        }

        template<typename T, typename color_type, typename size_type>
        const color_type *dispmanx_pixmap<T, color_type, size_type>::data() const {
            return m_data.get();
        }

    }  // namespace detail
    template<typename color_type, typename size_type = std::size_t>
    using dispmanx_pixmap = detail::dispmanx_pixmap<detail::bcm_host_type, color_type, size_type>;
}  // namespace bcm_host_wrapper
