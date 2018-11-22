#include "native/dispmanx_native.h"

int vc_dispmanx_rect_set(VC_RECT_T *, uint32_t, uint32_t, uint32_t, uint32_t) { return 0; }

DISPMANX_RESOURCE_HANDLE_T vc_dispmanx_resource_create(VC_IMAGE_TYPE_T, uint32_t, uint32_t, uint32_t *) { return 0; }

int vc_dispmanx_resource_write_data(DISPMANX_RESOURCE_HANDLE_T, VC_IMAGE_TYPE_T, int, void *, const VC_RECT_T *) {
    return 0;
}
int vc_dispmanx_resource_delete(DISPMANX_RESOURCE_HANDLE_T) { return 0; }

DISPMANX_ELEMENT_HANDLE_T vc_dispmanx_element_add(DISPMANX_UPDATE_HANDLE_T, DISPMANX_DISPLAY_HANDLE_T, int32_t,
                                                  const VC_RECT_T *, DISPMANX_RESOURCE_HANDLE_T, const VC_RECT_T *,
                                                  DISPMANX_PROTECTION_T, VC_DISPMANX_ALPHA_T *, DISPMANX_CLAMP_T *,
                                                  DISPMANX_TRANSFORM_T) {
    return 0;
}
DISPMANX_UPDATE_HANDLE_T vc_dispmanx_update_start(int32_t) { return 0; }

int vc_dispmanx_element_change_source(DISPMANX_UPDATE_HANDLE_T, DISPMANX_ELEMENT_HANDLE_T, DISPMANX_RESOURCE_HANDLE_T) {
    return 0;
}

int vc_dispmanx_element_change_layer(DISPMANX_UPDATE_HANDLE_T, DISPMANX_ELEMENT_HANDLE_T, int32_t) { return 0; }

int vc_dispmanx_element_modified(DISPMANX_UPDATE_HANDLE_T, DISPMANX_ELEMENT_HANDLE_T, const VC_RECT_T *) { return 0; }

int vc_dispmanx_element_remove(DISPMANX_UPDATE_HANDLE_T, DISPMANX_ELEMENT_HANDLE_T) { return 0; }

int vc_dispmanx_update_submit_sync(DISPMANX_UPDATE_HANDLE_T) { return 0; }

DISPMANX_DISPLAY_HANDLE_T vc_dispmanx_display_open(uint32_t) { return 0; }

int vc_dispmanx_display_close(DISPMANX_DISPLAY_HANDLE_T) { return 0; }

int vc_dispmanx_display_get_info(DISPMANX_DISPLAY_HANDLE_T, DISPMANX_MODEINFO_T *) { return 0; }
