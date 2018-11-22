#pragma once

#include "bcm_host_type.h"
#include "dispmanx_resource.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {
    /** \brief This class is a wrapper for the dispmanx struct VC_RECT_T it is used,
     * when a region has to be specified.
     */
    /** \brief This enum lists possible orientations which can be used to rotate the
     * display.
     */
    enum struct orientation {
        NO_ROTATION = DISPMANX_NO_ROTATE,
        ROTATE_90 = DISPMANX_ROTATE_90,
        ROTATE_180 = DISPMANX_ROTATE_180,
        ROTATE_270 = DISPMANX_ROTATE_270
    };

    // TODO Make chainable
    /** \brief This enum contains flags which signal if the display should by
     * flipped or not.
     */
    enum struct flipped { NO = 0, HORIZONTALLY = DISPMANX_FLIP_HRIZ, VERITCALLY = DISPMANX_FLIP_VERT };

    // TODO Make chainable
    enum struct snapshot_behaviour { NONE };

    namespace detail {

        // TODO Maybe implement other flags as well
        /** \brief This class contains all the information necessary to describe the
         * alignment of the display It contains information such as display rotation, or
         * snapshot_behaviour.
         */
        template<typename T>
        class dispmanx_transform {
           public:
            dispmanx_transform(const orientation &orient = orientation::NO_ROTATION, const flipped &flip = flipped::NO,
                               const snapshot_behaviour &behaviour = snapshot_behaviour::NONE);
            /** \brief Returns the underlying structure which is used by the vc_dispman*
             * calls.
             */
            DISPMANX_TRANSFORM_T native_transform() const;

           private:
            orientation m_orient;
            flipped m_flip;
            snapshot_behaviour m_behaviour;
        };

    }  // namespace detail
    using dispmanx_transform = detail::dispmanx_transform<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
