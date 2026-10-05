################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.20)
project(gz_random_objects)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 23)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

################################################################################
# Find ament packages and libraries for ament and system dependencies
################################################################################
# gazebo harmonic
find_package(gz-sim8 QUIET)
# gazebo jetty
find_package(gz-sim QUIET)

if(NOT gz-sim8_FOUND AND NOT gz-sim_FOUND)
    message(SEND_ERROR "Gazeboo 8 Harmonic or 10 Jetty was not found!")
    return()
endif()

set(INCLUDE_DEPENDS
    PkgConfig
    ament_cmake
)

if( gz-sim8_FOUND )
    set(INCLUDE_DEPENDS
        ${INCLUDE_DEPENDS}
        gz-cmake3
        gz-common5
        gz-gui8
        gz-math7
        gz-msgs10
        gz-physics7
        gz-plugin2
        gz-transport13
        gz-utils2
        sdformat14
    )
endif()

if( gz-sim_FOUND )
    set(INCLUDE_DEPENDS
        ${INCLUDE_DEPENDS}
        gz-cmake
        gz-common
        gz-gui
        gz-math
        gz-msgs
        gz-physics
        gz-plugin
        gz-transport
        gz-utils
        sdformat
    )
endif()

foreach(Dependency IN ITEMS ${INCLUDE_DEPENDS})
    find_package(${Dependency} REQUIRED)
endforeach()

################################################################################
# Build
################################################################################
if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    ament_lint_auto_find_test_dependencies()
endif()

include_directories(src)

include_directories(
    ${GZ-CMAKE_DIR}
    ${GZ-COMMON_INCLUDE_DIRS}
    ${GZ-SIM_INCLUDE_DIRS}
    ${GZ-MATH_INCLUDE_DIRS}
    ${GZ-MSGS_INCLUDE_DIRS}
    ${GZ-PHYSICS_INCLUDE_DIRS}
    ${GZ-PLUGIN_INCLUDE_DIRS}
    ${GZ-TRANSPORT_INCLUDE_DIRS}
    ${GZ-UTILS_INCLUDE_DIRS}
    ${SDFormat_INCLUDE_DIRS}
)

link_directories(${GZ-CMAKE_LIBRARY_DIRS}
    ${GZ-COMMON_LIBRARY_DIRS}
    ${GZ-SIM_LIBRARY_DIRS}
    ${GZ-MATH_LIBRARY_DIRS}
    ${GZ-MSGS_LIBRARY_DIRS}
    ${GZ-PLUGIN_LIBRARY_DIRS}
    ${GZ-PHYSICS_LIBRARY_DIRS}
    ${GZ-TRANSPORT_LIBRARY_DIRS}
    ${GZ-UTILS_LIBRARY_DIRS}
    ${SDFormat_LIBRARY_DIRS}
)

# shared object libraries, lib*.so
add_library(gz_random_objects SHARED src/GzRandomObjects.cc)

################################################################################
# Install
################################################################################
install(TARGETS gz_random_objects
    EXPORT gz_random_objects
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib/${PROJECT_NAME}
)

################################################################################
# Macro for ament package
################################################################################
ament_package()
