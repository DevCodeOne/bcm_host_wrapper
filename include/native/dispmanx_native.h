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

struct DISPMANX_MODEINFO_T {
    int32_t width;
    int32_t height;
    int8_t display_num;
};

struct VC_DISPMANX_ALPHA_T {};

struct DISPMANX_CLAMP_T {};

using DISPMANX_DISPLAY_HANDLE_T = uint32_t;
using DISPMANX_UPDATE_HANDLE_T = uint32_t;
using DISPMANX_ELEMENT_HANDLE_T = uint32_t;
using DISPMANX_RESOURCE_HANDLE_T = uint32_t;

using DISPMANX_PROTECTION_T = uint32_t;

// TODO replace with enums, at best in own namespaces so the global namespace
// isn't litered
inline constexpr int DISPMANX_NO_ROTATE = 0;
inline constexpr int DISPMANX_ROTATE_90 = 1;
inline constexpr int DISPMANX_ROTATE_180 = 2;
inline constexpr int DISPMANX_ROTATE_270 = 3;

inline constexpr int DISPMANX_FLIP_HRIZ = 1;
inline constexpr int DISPMANX_FLIP_VERT = 2;

inline constexpr int DISPMANX_FLAGS_ALPHA_FROM_SOURCE = 0;
inline constexpr int DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS = 1;
inline constexpr int DISPMANX_FLAGS_ALPHA_FIXED_NON_ZERO = 2;
inline constexpr int DISPMANX_FLAGS_ALPHA_FIXED_EXCEED_0X07 = 3;

inline constexpr int DISPMANX_FLAGS_ALPHA_PREMULT = 1 << 16;
inline constexpr int DISPMANX_FLAGS_ALPHA_MIX = 1 << 17;
inline constexpr int DISPMANX_FLAGS_ALPHA_DISCARD_LOWER_LAYERS = 1 << 18;

inline constexpr int DISPMANX_PROTECTION_MAX = 0;
inline constexpr int DISPMANX_PROTECTION_NONE = 1;
inline constexpr int DISPMANX_PROTECTION_HDCP = 2;

inline constexpr int VCOS_DISPLAY_INPUT_FORMAT_INVALID = 0;
inline constexpr int VCOS_DISPLAY_INPUT_FORMAT_RGB888 = 1;
inline constexpr int VCOS_DISPLAY_INPUT_FORMAT_RGB565 = 2;

inline constexpr int DISPMANX_ID_MAIN_LCD = 0;
inline constexpr int DISPMANX_ID_AUX_LCD = 1;
inline constexpr int DISPMANX_ID_HDMI = 2;
inline constexpr int DISPMANX_ID_SDTV = 3;
inline constexpr int DISPMANX_ID_FORCE_LCD = 4;
inline constexpr int DISPMANX_ID_FORCE_TV = 5;
inline constexpr int DISPMANX_ID_FORCE_OTHER = 6;

enum VC_IMAGE_TYPE_T { VC_IMAGE_RGBA32 };

int vc_dispmanx_rect_set(VC_RECT_T *, uint32_t, uint32_t, uint32_t, uint32_t);
DISPMANX_RESOURCE_HANDLE_T vc_dispmanx_resource_create(VC_IMAGE_TYPE_T,
                                                       uint32_t, uint32_t,
                                                       uint32_t *);
int vc_dispmanx_resource_write_data(DISPMANX_RESOURCE_HANDLE_T, VC_IMAGE_TYPE_T,
                                    int, void *, const VC_RECT_T *);
int vc_dispmanx_resource_delete(DISPMANX_RESOURCE_HANDLE_T);
DISPMANX_ELEMENT_HANDLE_T vc_dispmanx_element_add(
    DISPMANX_UPDATE_HANDLE_T, DISPMANX_DISPLAY_HANDLE_T, int32_t layer,
    const VC_RECT_T *, DISPMANX_RESOURCE_HANDLE_T, const VC_RECT_T *,
    DISPMANX_PROTECTION_T, VC_DISPMANX_ALPHA_T *, DISPMANX_CLAMP_T *,
    DISPMANX_TRANSFORM_T);
int vc_dispmanx_element_change_source(DISPMANX_UPDATE_HANDLE_T,
                                      DISPMANX_ELEMENT_HANDLE_T,
                                      DISPMANX_RESOURCE_HANDLE_T);
int vc_dispmanx_element_change_layer(DISPMANX_UPDATE_HANDLE_T,
                                     DISPMANX_ELEMENT_HANDLE_T, int32_t);
int vc_dispmanx_element_modified(DISPMANX_UPDATE_HANDLE_T,
                                 DISPMANX_ELEMENT_HANDLE_T, const VC_RECT_T *);
int vc_dispmanx_element_remove(DISPMANX_UPDATE_HANDLE_T,
                               DISPMANX_ELEMENT_HANDLE_T);
int vc_dispmanx_update_submit_sync(DISPMANX_UPDATE_HANDLE_T);
DISPMANX_DISPLAY_HANDLE_T vc_dispmanx_display_open(uint32_t);
int vc_dispmanx_display_close(DISPMANX_DISPLAY_HANDLE_T);
int vc_dispmanx_display_get_info(DISPMANX_DISPLAY_HANDLE_T,
                                 DISPMANX_MODEINFO_T *);

#endif
