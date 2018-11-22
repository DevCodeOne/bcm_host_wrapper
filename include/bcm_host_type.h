#pragma once

namespace bcm_host_wrapper::detail {

struct real {};
struct stub {};

#ifdef USE_BCM_HOST
#include "bcm_host.h"
using bcm_host_type = real;
#else
using bcm_host_type = stub;
#endif

}  // namespace bcm_host_wrapper::detail
