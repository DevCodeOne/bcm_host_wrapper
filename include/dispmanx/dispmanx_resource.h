#pragma once

#include <optional>
#include <type_traits>

#include "bcm_host_type.h"
#include "dispmanx_pixmap.h"
#include "dispmanx_rect.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {

    namespace detail {

        template<typename T>
        class dispmanx_update;

        /** \brief Class which contains the image data to display on the screen.
         * This class is used in conjunction with dispmanx_element. With those two
         * together it is possible to display something on the screen
         */
        template<typename T>
        class dispmanx_resource {
           public:
            static_assert(std::is_same_v<real, T> || std::is_same_v<stub, T>, "T can be detail::stub or detail::real");

            /** \brief Move construct an instance from another.
             */
            dispmanx_resource(dispmanx_resource &&other);
            ~dispmanx_resource();
            /** \brief Creates a new resource with the provided parameters.
             * If the creation of the dispmanx_resource fails for any reason no instance
             * will be returned
             */
            static std::optional<dispmanx_resource> create_resource(const VC_IMAGE_TYPE_T &image_type, uint32_t width,
                                                                    uint32_t height);
            /** \brief Writes the data of the pixmap into the resource.
             */
            template<typename T2>
            void write_data(VC_IMAGE_TYPE_T src_type, const bcm_host_wrapper::dispmanx_pixmap<T2> &pixmap,
                            const bcm_host_wrapper::dispmanx_rect &region);
            /** \brief Reads data from the resource into the pixmap.
             */
            template<typename T2>
            void read_data(const bcm_host_wrapper::dispmanx_rect &region,
                           bcm_host_wrapper::dispmanx_pixmap<T2> &pixmap);

            /** \brief Returns the dimensions (widthxheight) of the resource.
             */
            const bcm_host_wrapper::dispmanx_rect &dimensions() const;

           private:
            dispmanx_resource(const DISPMANX_RESOURCE_HANDLE_T &handle, const VC_IMAGE_TYPE_T &image_type,
                              uint32_t width, uint32_t height);

            const DISPMANX_RESOURCE_HANDLE_T &handle() const;

            /** \brief Underlying structure to interface with vc_dispman* call.
             */
            DISPMANX_RESOURCE_HANDLE_T m_handle;
            const VC_IMAGE_TYPE_T m_image_type;
            const bcm_host_wrapper::dispmanx_rect m_dimensions;

            friend class dispmanx_update<T>;
        };

        template<typename T>
        template<typename T2>
        void dispmanx_resource<T>::write_data(VC_IMAGE_TYPE_T src_type,
                                              const bcm_host_wrapper::dispmanx_pixmap<T2> &pixmap,
                                              const bcm_host_wrapper::dispmanx_rect &region) {
            vc_dispmanx_resource_write_data(m_handle, src_type, pixmap.pitch() * sizeof(T2), (void *)pixmap.data(),
                                            &region.rect());
        }

        template<typename T>
        template<typename T2>
        void dispmanx_resource<T>::read_data(const bcm_host_wrapper::dispmanx_rect &region,
                                             bcm_host_wrapper::dispmanx_pixmap<T2> &pixmap) {
            vc_dispmanx_resource_read_data(m_handle, &region.rect(), (void *)pixmap.data(), pixmap.pitch());
        }

        template<typename T>
        std::optional<dispmanx_resource<T>> dispmanx_resource<T>::create_resource(const VC_IMAGE_TYPE_T &image_type,
                                                                                  uint32_t width, uint32_t height) {
            uint32_t native_image_handle = 0;
            DISPMANX_RESOURCE_HANDLE_T handle =
                vc_dispmanx_resource_create(image_type, width, height, &native_image_handle);

            if (handle == 0) {
                return {};
            }

            return dispmanx_resource(handle, image_type, width, height);
        }

        template<typename T>
        dispmanx_resource<T>::dispmanx_resource(const DISPMANX_RESOURCE_HANDLE_T &handle,
                                                const VC_IMAGE_TYPE_T &image_type, uint32_t width, uint32_t height)
            : m_handle(handle), m_image_type(image_type), m_dimensions(0, 0, width, height) {}

        template<typename T>
        dispmanx_resource<T>::dispmanx_resource(dispmanx_resource &&other)
            : m_handle(std::move(other.m_handle)), m_image_type(other.m_image_type), m_dimensions(other.m_dimensions) {
            other.m_handle = 0;
        }

        template<typename T>
        dispmanx_resource<T>::~dispmanx_resource() {
            vc_dispmanx_resource_delete(m_handle);
        }

        template<typename T>
        const DISPMANX_RESOURCE_HANDLE_T &dispmanx_resource<T>::handle() const {
            return m_handle;
        }

        template<typename T>
        const bcm_host_wrapper::dispmanx_rect &dispmanx_resource<T>::dimensions() const {
            return m_dimensions;
        }

    }  // namespace detail
    using dispmanx_resource = detail::dispmanx_resource<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
