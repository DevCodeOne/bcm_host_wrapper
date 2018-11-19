cmake_minimum_required(VERSION 3.6.2)
project(bcm_host_wrapper C CXX)
# set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_compile_options(-Wall -Wextra -Wpedantic -Wno-variadic-macros -Wno-psabi -g)
add_definitions(-DSPDLOG_ENABLE_SYSLOG=1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

# pkg_check_modules(PC_BCM_HOST REQUIRED QUIET bcm_host)
# link_directories(${PC_BCM_HOST_LIBRARY_DIRS})

set (SOURCE_FILES src/bcm_host_wrapper.cpp)

add_library(bcm_host_wrapper ${SOURCE_FILES})
set_property(TARGET bcm_host_wrapper PROPERTY CXX_STANDARD 17)

target_include_directories(bcm_host_wrapper PRIVATE include)

target_link_libraries(bcm_host_wrapper PRIVATE stdc++fs)
target_link_libraries(bcm_host_wrapper PRIVATE pthread)

add_executable(bcm_host_wrapper_test tests/bcm_host_wrapper_test.cpp)
set_property(TARGET bcm_host_wrapper_test PROPERTY CXX_STANDARD 17)

target_include_directories(bcm_host_wrapper_test PRIVATE stdc++fs)
target_include_directories(bcm_host_wrapper_test PRIVATE pthread)
target_include_directories(bcm_host_wrapper_test PRIVATE include)
target_link_libraries(bcm_host_wrapper_test PRIVATE bcm_host_wrapper)
