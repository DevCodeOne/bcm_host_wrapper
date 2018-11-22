#include "bcm_host_wrapper.h"
#include "dispmanx/dispmanx_wrapper.h"

int main() {
    auto bcm_instance = bcm_host_wrapper::bcm_host::instance();
    auto display = bcm_host_wrapper::dispmanx_display::open_display(bcm_host_wrapper::dispmanx_display_ids::HDMI);

    return 0;
}
