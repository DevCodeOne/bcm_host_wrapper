#pragma once

#include <memory>
#include <mutex>

#include "native/bcm_host_native.h"

namespace bcm_host_wrapper {
namespace detail {

template <typename T>
class bcm_host;

template <>
class bcm_host<stub> {
   public:
    static std::shared_ptr<bcm_host> instance();
    ~bcm_host() = default;

   private:
    bcm_host() = default;

    static inline std::shared_ptr<bcm_host> _instance{nullptr};
    static inline std::mutex _instance_mutex{};
};

std::shared_ptr<bcm_host<stub>> bcm_host<stub>::instance() {
    std::lock_guard<std::mutex> instance_guard{_instance_mutex};

    if (_instance == nullptr) {
        _instance = std::shared_ptr<bcm_host<stub>>(new bcm_host<stub>);
    }

    return _instance;
}

template <>
class bcm_host<real> {
   public:
    static std::shared_ptr<bcm_host> instance();
    ~bcm_host();

   private:
    bcm_host();

    static inline std::shared_ptr<bcm_host> _instance{nullptr};
    static inline std::mutex _instance_mutex{};
};
}  // namespace detail

using bcm_host = detail::bcm_host<detail::bcm_host_type>;

}  // namespace bcm_host_wrapper
