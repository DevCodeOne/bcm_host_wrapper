#pragma once

#include <cstdint>

#include "native/bcm_host_native.h"

#ifdef USE_BCM_HOST
// TODO include real dispmanx
#else
// Define all needed structs as empty structs since they are not actually used
struct VC_RECT_T {};
struct DISPMANX_TRANSFORM_T {};
struct VC_IMAGE_T {};

using DISPMANX_DISPLAY_HANDLE_T = uint32_t;
using DISPMANX_UPDATE_HANDLE_T = uint32_t;
using DISPMANX_ELEMENT_HANDLE_T = uint32_t;
using DISPMANX_RESOURCE_HANDLE_T = uint32_t;

using DISPMANX_PROTECTION_T = uint32_t;

// TODO replace with enums, at best in own namespaces so the global namespace isn't litered
#define DISPMANX_NO_ROTATE 0
#define DISPMANX_ROTATE_90 1
#define DISPMANX_ROTATE_180 2
#define DISPMANX_ROTATE_270 3

#define DISPMANX_FLIP_HRIZ 1
#define DISPMANX_FLIP_VERT 2

#endif

enum struct dispmanx_orientation {
    dispmanx_no_rotate = DISPMANX_NO_ROTATE,
    dispmanx_rotate_90 = DISPMANX_ROTATE_90,
    dispmanx_rotate_180 = DISPMANX_ROTATE_180,
    dispmanx_rotate_270 = DISPMANX_ROTATE_270
};

enum struct dispmanx_flip {
    no = 0,
    horizontally = DISPMANX_FLIP_HRIZ,
    vertically = DISPMANX_FLIP_VERT
};

// TODO set from values
enum struct dispmanx_alpha_flags {
    from_source,
    fixed_all_pixels,
    fixed_non_zero,
    fixed_exceed_0x07,
    premult,
    mix,
    discard_lower_layers,
};
