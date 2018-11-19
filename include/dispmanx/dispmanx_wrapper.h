#pragma once

#include "native/bcm_host_native.h"
#include "dispmanx/dispmanx_data_types_wrapper.h"

namespace bcm_host_wrapper {
namespace detail {
template <typename T>
class dispmanx;

template <>
class dispmanx<stub> {};

template <>
class dispmanx<real> {};

}  // namespace detail

using dispmanx = detail::dispmanx<detail::bcm_host_type>;

}  // namespace bcm_host_wrapper
