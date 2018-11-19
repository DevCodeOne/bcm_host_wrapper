#include "bcm_host_wrapper.h"
#include "dispmanx/dispmanx_wrapper.h"

int main() {
    auto bcm_instance = bcm_host_wrapper::bcm_host::instance();
    bcm_host_wrapper::dispmanx_rect rect;

    return 0;
}
