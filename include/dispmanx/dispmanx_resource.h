#pragma once

#include <optional>

#include "bcm_host_type.h"
#include "dispmanx_pixmap.h"
#include "dispmanx_rect.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {
    namespace detail {

        /** \brief Class which contains the image data to display on the screen.
         * This class is used in conjunction with dispmanx_element. With those two
         * together it is possible to display something on the screen
         */
        template<typename T>
        class dispmanx_resource;

        template<>
        class dispmanx_resource<stub> {
           public:
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
            template<typename T>
            void write_data(VC_IMAGE_TYPE_T src_type, const bcm_host_wrapper::dispmanx_pixmap<T> &pixmap,
                            const bcm_host_wrapper::dispmanx_rect &region);
            /** \brief Reads data from the resource into the pixmap.
             */
            template<typename T>
            void read_data(const bcm_host_wrapper::dispmanx_rect &region, bcm_host_wrapper::dispmanx_pixmap<T> &pixmap);

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
        };

        template<>
        class dispmanx_resource<real> {
           public:
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
            template<typename T>
            void write_data(VC_IMAGE_TYPE_T src_type, const bcm_host_wrapper::dispmanx_pixmap<T> &pixmap,
                            const bcm_host_wrapper::dispmanx_rect &region);
            /** \brief Reads data from the resource into the pixmap.
             */
            template<typename T>
            void read_data(const bcm_host_wrapper::dispmanx_rect &region, bcm_host_wrapper::dispmanx_pixmap<T> &pixmap);

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

            template<typename T>
            friend class dispmanx_update;
        };

        template<typename T2>
        void dispmanx_resource<real>::write_data(VC_IMAGE_TYPE_T src_type,
                                                 const bcm_host_wrapper::dispmanx_pixmap<T2> &pixmap,
                                                 const bcm_host_wrapper::dispmanx_rect &region) {
            vc_dispmanx_resource_write_data(m_handle, src_type, pixmap.pitch() * sizeof(T2), (void *)pixmap.data(),
                                            &region.rect());
        }

        template<typename T2>
        void dispmanx_resource<real>::read_data(const bcm_host_wrapper::dispmanx_rect &region,
                                                bcm_host_wrapper::dispmanx_pixmap<T2> &pixmap) {
            vc_dispmanx_resource_read_data(m_handle, &region.rect(), (void *)pixmap.data(), pixmap.pitch());
        }

    }  // namespace detail
    using dispmanx_resource = detail::dispmanx_resource<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
