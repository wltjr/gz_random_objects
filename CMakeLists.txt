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
# gazebo fortress
find_package(ignition-gazebo6 QUIET)
# gazebo harmonic
find_package(gz-sim8 QUIET)

if(NOT ignition-gazebo6_FOUND AND NOT gz-sim8_FOUND )
    message(SEND_ERROR "Gazeboo 6 Fortress or 8 Harmonic was not found!")
    return()
endif()

set(INCLUDE_DEPENDS
    PkgConfig
    ament_cmake
)

if( ignition-gazebo6_FOUND )
    set(INCLUDE_DEPENDS
        ${INCLUDE_DEPENDS}
        ignition-cmake2
        ignition-common4
        ignition-gazebo6
        ignition-math6
        ignition-msgs8
        ignition-physics5
        ignition-plugin1
        ignition-transport11
        ignition-utils1
        sdformat12
    )
    add_definitions(-DUSE_GZ6)
endif()

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
    add_definitions(-DUSE_GZ8)
endif()

foreach(Dependency IN ITEMS ${INCLUDE_DEPENDS})
    find_package(${Dependency} REQUIRED)
endforeach()

if( ignition-gazebo6_FOUND )
    pkg_search_module(ignition-cmake2 REQUIRED ignition-cmake2)
endif()

if( gz-sim8_FOUND )
    pkg_search_module(gz-cmake3 REQUIRED gz-cmake3)
endif()

################################################################################
# Build
################################################################################
if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    ament_lint_auto_find_test_dependencies()
endif()

include_directories(src)

if( ignition-gazebo6_FOUND )
    include_directories(
        ${IGNITION-CMAKE_DIR}
        /usr/include/ignition/cmake2/
        ${IGNITION-COMMON_INCLUDE_DIRS}
        ${IGNITION-GAZEBO_INCLUDE_DIRS}
        ${IGNITION-MATH_INCLUDE_DIRS}
        ${IGNITION-MSGS_INCLUDE_DIRS}
        ${IGNITION-PHYSICS_INCLUDE_DIRS}
        ${IGNITION-PLUGIN_INCLUDE_DIRS}
        ${IGNITION-TRANSPORT_INCLUDE_DIRS}
        ${IGNITION-UTILS_INCLUDE_DIRS}
        ${SDFormat_INCLUDE_DIRS}
    )

    link_directories(${IGNITION-CMAKE_LIBRARY_DIRS}
        ${IGNITION-COMMON_LIBRARY_DIRS}
        ${IGNITION-GAZEBO_LIBRARY_DIRS}
        ${IGNITION-MATH_LIBRARY_DIRS}
        ${IGNITION-MSGS_LIBRARY_DIRS}
        ${IGNITION-PLUGIN_LIBRARY_DIRS}
        ${IGNITION-PHYSICS_LIBRARY_DIRS}
        ${IGNITION-TRANSPORT_LIBRARY_DIRS}
        ${IGNITION-UTILS_LIBRARY_DIRS}
        ${SDFormat_LIBRARY_DIRS}
    )
endif()

if( gz-sim8_FOUND )
    include_directories(
        ${GZ-CMAKE_DIR}
        /opt/ros/jazzy/opt/gz_cmake_vendor/include/gz/cmake3/
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
endif()

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
