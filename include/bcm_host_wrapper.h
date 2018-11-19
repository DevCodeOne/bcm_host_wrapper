#pragma once

namespace bcm_host_wrapper {
namespace detail {

#if __has_include("bcm_host.h")
#include "bcm_host.h"
#endif

struct real {};
struct stub {};

template <typename T>
class bcm_host;

template <>
class bcm_host<stub> {
   public:
   private:
};

template <>
class bcm_host<real> {
   public:
   private
};
}  // namespace detail
}  // namespace bcm_host_wrapper
