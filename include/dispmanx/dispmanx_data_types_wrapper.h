#pragma once

#include "native/bcm_host_native.h"
#include "native/dispmanx_native.h"

namespace bcm_host_wrapper {
namespace detail {
template <typename T>
class dispmanx_rect;

template <>
class dispmanx_rect<stub> {};

template <>
class dispmanx_rect<real> {
    VC_RECT_T m_rect;
};
}  // namespace detail
using dispmanx_rect = detail::dispmanx_rect<detail::bcm_host_type>;
}  // namespace bcm_host_wrapper
