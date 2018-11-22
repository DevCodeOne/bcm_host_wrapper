#pragma once

#include <cstdint>
#include <memory>
#include <optional>

#include "dispmanx/dispmanx_alpha.h"
#include "dispmanx/dispmanx_clamp.h"
#include "dispmanx/dispmanx_display.h"
#include "dispmanx/dispmanx_element_handle.h"
#include "dispmanx/dispmanx_modeinfo.h"
#include "dispmanx/dispmanx_pixmap.h"
#include "dispmanx/dispmanx_rect.h"
#include "dispmanx/dispmanx_resource.h"
#include "dispmanx/dispmanx_transform.h"
#include "dispmanx/dispmanx_update.h"
#include "dispmanx/dispmanx_wrapper.h"

namespace bcm_host_wrapper {

    // enum struct dispmanx_orientation {
    //     dispmanx_no_rotate = DISPMANX_NO_ROTATE,
    //     dispmanx_rotate_90 = DISPMANX_ROTATE_90,
    //     dispmanx_rotate_180 = DISPMANX_ROTATE_180,
    //     dispmanx_rotate_270 = DISPMANX_ROTATE_270
    // };

    // enum struct dispmanx_flip { no = 0, horizontally = DISPMANX_FLIP_HRIZ, vertically = DISPMANX_FLIP_VERT };

    // enum struct dispmanx_image_types { rgba_32 = 0 };

    namespace detail {}  // namespace detail

}  // namespace bcm_host_wrapper
