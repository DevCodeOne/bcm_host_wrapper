cmake_minimum_required(VERSION 3.6.2)
project(bcm_host_wrapper C CXX)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-variadic-macros -Wno-psabi -g)
add_definitions(-DSPDLOG_ENABLE_SYSLOG=1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

option(USE_BCM_HOST "Use the real bcm host library instead of the stub library" ON)
option(BUILD_TESTS "Build tests to test the wrapper" ON)

if (USE_BCM_HOST)
    find_package(PkgConfig)
    pkg_check_modules(PC_BCM_HOST REQUIRED QUIET bcm_host)
    link_directories(${PC_BCM_HOST_LIBRARY_DIRS})
endif()

set (SOURCE_FILES src/bcm_host_wrapper.cpp)

if (NOT USE_BCM_HOST)
    set (SOURCE_FILES ${SOURCE_FILES} src/native/dispmanx_native.cpp)
    set (SOURCE_FILES ${SOURCE_FILES} src/native/bcm_host_native.cpp)
endif ()

add_library(bcm_host_wrapper ${SOURCE_FILES})
set_property(TARGET bcm_host_wrapper PROPERTY CXX_STANDARD 17)

target_include_directories(bcm_host_wrapper PRIVATE include)

target_link_libraries(bcm_host_wrapper PRIVATE stdc++fs)
target_link_libraries(bcm_host_wrapper PRIVATE pthread)

if (BUILD_TESTS)
    add_executable(bcm_host_wrapper_test tests/bcm_host_wrapper_test.cpp)
    set_property(TARGET bcm_host_wrapper_test PROPERTY CXX_STANDARD 17)

    target_include_directories(bcm_host_wrapper_test PRIVATE include)

    target_link_libraries(bcm_host_wrapper_test PRIVATE stdc++fs)
    target_link_libraries(bcm_host_wrapper_test PRIVATE pthread)
    target_link_libraries(bcm_host_wrapper_test PRIVATE bcm_host_wrapper)
endif ()

if (USE_BCM_HOST)
    target_link_libraries(lp PRIVATE ${PC_BCM_HOST_LIBRARIES})
    target_include_directories(lp PRIVATE ${PC_BCM_HOST_INCLUDE_DIRS})
    target_compile_options(lp PRIVATE ${PC_BCM_CFLAGS_OTHER})

    if (BUILD_TESTS)
        target_link_libraries(bcm_host_wrapper_test PRIVATE ${PC_BCM_HOST_LIBRARIES})
        target_include_directories(bcm_host_wrapper_test PRIVATE ${PC_BCM_HOST_INCLUDE_DIRS})
        target_compile_options(bcm_host_wrapper_test PRIVATE ${PC_BCM_CFLAGS_OTHER})
    endif ()
endif ()
